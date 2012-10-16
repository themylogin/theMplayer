#include "Utils.h"

extern "C"
{
    #define __STDC_CONSTANT_MACROS
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
}
#include <QApplication>
#include <QDesktopWidget>
#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>

bool Utils::avRegistered = false;
QMutex Utils::avRegisteredMutex;
QMutex Utils::avCodecMutex;

void Utils::getWidestScreenDimensions(int& width, int& height)
{
    width = 0;
    height = 0;
    for (int screen = 0; screen < QApplication::desktop()->screenCount(); screen++)
    {
        if (QApplication::desktop()->screenGeometry(screen).width() > width)
        {
            width = QApplication::desktop()->screenGeometry(screen).width();
            height = QApplication::desktop()->screenGeometry(screen).height();
        }
    }
}

QStringList Utils::wrapText(const QFont& font, const QString& text, int width)
{
    QStringList lines;
    QFontMetrics metrics(font);
    QString notWrappedTextPart = text;
    while (notWrappedTextPart != "")
    {
        bool wrapped = false;
        for (int i = 1; i < notWrappedTextPart.length(); i++)
        {
            if (metrics.boundingRect(notWrappedTextPart.left(i)).width() > width)
            {
                if (i > 1)
                {
                    // try to cut by whitespace
                    int j = i - 1;
                    while (j >= 0 && notWrappedTextPart[j] != ' ')
                    {
                        j--;
                    }
                    if (j > 0)
                    {
                        lines.append(notWrappedTextPart.left(j));
                        notWrappedTextPart = notWrappedTextPart.mid(j + 1);
                    }
                    else
                    {
                        lines.append(notWrappedTextPart.left(i - 1));
                        notWrappedTextPart = notWrappedTextPart.mid(i - 1);
                    }
                }
                else
                {
                    notWrappedTextPart = notWrappedTextPart.mid(i);
                }
                wrapped = true;
                break;
            }
        }
        if (!wrapped)
        {
            lines.append(notWrappedTextPart);
            break;
        }
    }

    return lines;
}

QImage Utils::drawOutlinedText(QString text, int width, int height)
{
    int fontSize = 32;
    int lineHeight = 42;
    int textHPadding = 20;
    int textVPadding = 20;
    QFont font = QFont("Impact", fontSize, 800, false);
    QStringList lines = Utils::wrapText(font, text, width - 2 * textHPadding);

    QImage image = QImage(QSize(width, height), QImage::Format_ARGB32);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(QColor(0, 0, 0));
    pen.setWidth(3);
    painter.setPen(pen);
    painter.setBrush(QColor(255, 255, 255));
    QFontMetrics metrics(font);
    for (int i = 0; i < lines.length(); i++)
    {
        QRect lineRect = metrics.boundingRect(lines[i]);

        QPainterPath path;
        path.addText((width - lineRect.width()) / 2,
                     (height - textVPadding - lineHeight * (lines.length() - i - 1)),
                     font, lines[i]);
        painter.drawPath(path);
    }
    return image;
}

QImage Utils::getMovieThumbnail(QString filename)
{
    QImage thumbnail;
    AVFormatContext* avFormatContext = NULL;
    int videoIndex = -1;
    AVCodec* avCodec;
    AVFrame* avFrame;
    int gotFrame;
    AVPacket packet;
    AVFrame* avFrameRGB;
    int avFrameRGBbufferSize;
    uchar* avFrameRGBbuffer;
    int64_t middleFrame;
    struct SwsContext* scConvertContext;
    uchar* imageBuffer;

    Utils::avRegisteredMutex.lock();
    if (!Utils::avRegistered)
    {
        av_register_all();
        Utils::avRegistered = true;
    }
    Utils::avRegisteredMutex.unlock();

    if (avformat_open_input(&avFormatContext, filename.toUtf8(), NULL, NULL) != 0)
    {
        return thumbnail;
    }

    Utils::avCodecMutex.lock();
    if (avformat_find_stream_info(avFormatContext, NULL) < 0)
    {
        goto freeAvFormatContext;
    }
    Utils::avCodecMutex.unlock();

    for (unsigned int i = 0; i < avFormatContext->nb_streams; i++)
    {
        if (avFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoIndex = i;
        }
    }
    if (videoIndex == -1)
    {
        goto freeAvFormatContext;
    }

    avCodec = avcodec_find_decoder(avFormatContext->streams[videoIndex]->codec->codec_id);
    if (avCodec == NULL)
    {
        goto freeAvFormatContext;
    }

    Utils::avCodecMutex.lock();
    if (avcodec_open2(avFormatContext->streams[videoIndex]->codec, avCodec, NULL) < 0)
    {
        Utils::avCodecMutex.unlock();
        goto freeAvCodec;
    }
    Utils::avCodecMutex.unlock();

    if (avFormatContext->duration / AV_TIME_BASE < 1)
    {
        goto freeAvCodec;
    }

    avFrame = avcodec_alloc_frame();
    if (avFrame == NULL)
    {
        goto freeAvCodec;
    }

    middleFrame = avFormatContext->duration / AV_TIME_BASE / 2 *
                  (int) (((float) avFormatContext->streams[videoIndex]->r_frame_rate.num
                        / (float) avFormatContext->streams[videoIndex]->r_frame_rate.den) + 0.5);
    av_seek_frame(avFormatContext, videoIndex, middleFrame, 0);

    while (av_read_frame(avFormatContext, &packet) >= 0)
    {
        if (packet.stream_index == videoIndex)
        {
            avcodec_decode_video2(avFormatContext->streams[videoIndex]->codec, avFrame, &gotFrame, &packet);

            if (gotFrame)
            {
                av_free_packet(&packet);
                break;
            }
        }

        av_free_packet(&packet);
    }

    avFrameRGB = avcodec_alloc_frame();
    if (avFrameRGB == NULL)
    {
        goto freeAvFrame;
    }

    avFrameRGBbufferSize = avpicture_get_size(PIX_FMT_RGB24, avFormatContext->streams[videoIndex]->codec->width, avFormatContext->streams[videoIndex]->codec->height);
    avFrameRGBbuffer = (uchar*) av_malloc(avFrameRGBbufferSize);
    if (avFrameRGBbuffer == NULL)
    {
        goto freeAvFrameRGB;
    }
    avpicture_fill((AVPicture*) avFrameRGB, avFrameRGBbuffer, PIX_FMT_RGB24,
                   avFormatContext->streams[videoIndex]->codec->width,
                   avFormatContext->streams[videoIndex]->codec->height);

    scConvertContext = sws_getContext(avFormatContext->streams[videoIndex]->codec->width, avFormatContext->streams[videoIndex]->codec->height, avFormatContext->streams[videoIndex]->codec->pix_fmt,
                                      avFormatContext->streams[videoIndex]->codec->width, avFormatContext->streams[videoIndex]->codec->height, PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);
    if (scConvertContext == NULL)
    {
        goto freeAvFrameRGBbuffer;
    }

    sws_scale(scConvertContext, avFrame->data, avFrame->linesize, 0,
              avFormatContext->streams[videoIndex]->codec->height,
              avFrameRGB->data, avFrameRGB->linesize);

    imageBuffer = new uchar[avFormatContext->streams[videoIndex]->codec->width * avFormatContext->streams[videoIndex]->codec->height * 3];
    memcpy(imageBuffer, avFrameRGB->data[0], avFormatContext->streams[videoIndex]->codec->width * avFormatContext->streams[videoIndex]->codec->height * 3);
    thumbnail = QImage(imageBuffer, avFormatContext->streams[videoIndex]->codec->width, avFormatContext->streams[videoIndex]->codec->height, QImage::Format_RGB888);

    freeSwsContext:
        sws_freeContext(scConvertContext);
    freeAvFrameRGBbuffer:
        av_free(avFrameRGBbuffer);
    freeAvFrameRGB:
        av_free(avFrameRGB);
    freeAvFrame:
        av_free(avFrame);
    freeAvCodec:
        Utils::avCodecMutex.lock();
        avcodec_close(avFormatContext->streams[videoIndex]->codec);
        Utils::avCodecMutex.unlock();
    freeAvFormatContext:
        Utils::avCodecMutex.lock();
        avformat_close_input(&avFormatContext);
        Utils::avCodecMutex.unlock();

    return thumbnail;
}

QImage Utils::loadImageFromFile(QString filename)
{
    return QImage(filename);
}
