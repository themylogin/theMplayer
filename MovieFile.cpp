#include <QString>

#include "MovieFile.h"

bool MovieFile::avRegistered = false;

MovieFile::MovieFile(QString filename)
{
    if (!avRegistered)
    {
        av_register_all();
        avRegistered = true;
    }
    avFormatContext = NULL;

    frameAllocated = false;

    if (avformat_open_input(&avFormatContext, filename.toUtf8(), NULL, NULL) != 0)
    {
        throw UnableToOpenFile;
    }

    if (avformat_find_stream_info(avFormatContext, NULL) < 0)
    {
        throw UnableToFindStreamInformation;
    }

    videoIndex = -1;
    for (unsigned int i = 0; i < avFormatContext->nb_streams; i++)
    {
        if (avFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoIndex = i;
        }
    }
    if (videoIndex == -1)
    {
        throw UnableToFindVideoStream;
    }

    avCodec = avcodec_find_decoder(avFormatContext->streams[videoIndex]->codec->codec_id);
    if (avCodec == NULL)
    {
        throw UnableToFindDecoder;
    }

    if (avcodec_open2(avFormatContext->streams[videoIndex]->codec, avCodec, NULL) < 0)
    {
        throw UnableToOpenDecoder;
    }

    if (getDuration() < 1)
    {
        throw NotAVideoFile;
    }
}

MovieFile::~MovieFile()
{
    if (avFormatContext != NULL)
    {
        if (avCodec != NULL)
        {
            avcodec_close(avFormatContext->streams[videoIndex]->codec);
        }

        avformat_close_input(&avFormatContext);
    }

    if (frameAllocated)
    {
        freeFrame();
    }
}

int64_t MovieFile::getDuration() const
{
    return avFormatContext->duration / AV_TIME_BASE;
}

uint8_t *MovieFile::getRGB32Thumbnail(int &width, int &height)
{
    if (width == -1)
    {
        width = (int)((float)avFormatContext->streams[videoIndex]->codec->width
                      * ((float)height / (float)avFormatContext->streams[videoIndex]->codec->height));
    } else if (height == -1) {
        height = (int)((float)avFormatContext->streams[videoIndex]->codec->height
                      * ((float)width / (float)avFormatContext->streams[videoIndex]->codec->width));
    }

    if (!frameAllocated)
    {
        allocateFrame();
    }

    int64_t middleFrame = getDuration() / 2 * (int)
                          (((float)avFormatContext->streams[videoIndex]->r_frame_rate.num
                             / (float)avFormatContext->streams[videoIndex]->r_frame_rate.den) + 0.5);
    av_seek_frame(avFormatContext, videoIndex, middleFrame, 0);
    readFrame();

    avFrameRGB = avcodec_alloc_frame();
    if (avFrameRGB == NULL)
    {
        throw std::bad_alloc();
    }

    int numBytes = avpicture_get_size(PIX_FMT_RGB32, width, height);
    buffer = new uint8_t[numBytes];
    avpicture_fill((AVPicture *)avFrameRGB, buffer, PIX_FMT_RGB32, width, height);

    struct SwsContext *scConvertContext = sws_getContext(avFormatContext->streams[videoIndex]->codec->width,
                                                         avFormatContext->streams[videoIndex]->codec->height,
                                                         avFormatContext->streams[videoIndex]->codec->pix_fmt,
                                                         width, height, PIX_FMT_RGB32,
                                                         SWS_BICUBIC, NULL, NULL, NULL);
    if (scConvertContext == NULL)
    {
        throw UnableToGetSwScaleContext;
    }

    sws_scale(scConvertContext, avFrame->data, avFrame->linesize, 0,
              avFormatContext->streams[videoIndex]->codec->height,
              avFrameRGB->data, avFrameRGB->linesize);

    return avFrameRGB->data[0];
}

void MovieFile::allocateFrame()
{
    avFrame = avcodec_alloc_frame();
    if (avFrame == NULL)
    {
        throw std::bad_alloc();
    }

    frameAllocated = true;
}

void MovieFile::readFrame()
{
    if (!frameAllocated)
    {
        allocateFrame();
    }

    AVPacket packet;
    int gotFrame;
    while (av_read_frame(avFormatContext, &packet) >= 0)
    {
        if (packet.stream_index == videoIndex)
        {
            avcodec_decode_video2(avFormatContext->streams[videoIndex]->codec, avFrame,
                                  &gotFrame, &packet);

            if (gotFrame)
            {
                av_free_packet(&packet);
                return;
            }
        }

        av_free_packet(&packet);
    }
}

void MovieFile::freeFrame()
{
    av_free(avFrame);
    frameAllocated = false;
}
