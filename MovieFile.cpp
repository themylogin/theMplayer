#include "MovieFile.h"

#include <QString>

bool MovieFile::avRegistered = false;

MovieFile::MovieFile(QString filename)
{
    if (!MovieFile::avRegistered)
    {
        av_register_all();
        MovieFile::avRegistered = true;
    }
    this->avFormatContext = NULL;

    this->frameAllocated = false;

    if (avformat_open_input(&this->avFormatContext, filename.toUtf8(), NULL, NULL) != 0)
    {
        throw UnableToOpenFile;
    }

    if (avformat_find_stream_info(this->avFormatContext, NULL) < 0)
    {
        throw UnableToFindStreamInformation;
    }

    this->videoIndex = -1;
    for (unsigned int i = 0; i < this->avFormatContext->nb_streams; i++)
    {
        if (this->avFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            this->videoIndex = i;
        }
    }
    if (this->videoIndex == -1)
    {
        throw UnableToFindVideoStream;
    }

    this->avCodec = avcodec_find_decoder(this->avFormatContext->streams[this->videoIndex]->codec->codec_id);
    if (this->avCodec == NULL)
    {
        throw UnableToFindDecoder;
    }

    if (avcodec_open2(this->avFormatContext->streams[this->videoIndex]->codec, this->avCodec, NULL) < 0)
    {
        throw UnableToOpenDecoder;
    }

    if (this->getDuration() < 1)
    {
        throw NotAVideoFile;
    }
}

MovieFile::~MovieFile()
{
    if (this->avFormatContext != NULL)
    {
        if (this->avCodec != NULL)
        {
            avcodec_close(this->avFormatContext->streams[this->videoIndex]->codec);
        }

        avformat_close_input(&this->avFormatContext);
    }

    if (this->frameAllocated)
    {
        this->freeFrame();
    }
}

int64_t MovieFile::getDuration() const
{
    return this->avFormatContext->duration / AV_TIME_BASE;
}

uint8_t* MovieFile::getRGB32Thumbnail(int& width, int& height)
{
    if (width == -1)
    {
        width = (int) ((float) this->avFormatContext->streams[this->videoIndex]->codec->width
                    * ((float) height / (float) this->avFormatContext->streams[this->videoIndex]->codec->height));
    }
    else if (height == -1)
    {
        height = (int) ((float) this->avFormatContext->streams[this->videoIndex]->codec->height
                     * ((float) width / (float) this->avFormatContext->streams[this->videoIndex]->codec->width));
    }

    if (!this->frameAllocated)
    {
        this->allocateFrame();
    }

    int64_t middleFrame = this-> getDuration() / 2 *
                          (int) (((float) this->avFormatContext->streams[this->videoIndex]->r_frame_rate.num
                                / (float) this->avFormatContext->streams[this->videoIndex]->r_frame_rate.den) + 0.5);
    av_seek_frame(this->avFormatContext, this->videoIndex, middleFrame, 0);
    this->readFrame();

    this->avFrameRGB = avcodec_alloc_frame();
    if (this->avFrameRGB == NULL)
    {
        throw std::bad_alloc();
    }

    int numBytes = avpicture_get_size(PIX_FMT_RGB32, width, height);
    this->buffer = new uint8_t[numBytes];
    avpicture_fill((AVPicture *) this->avFrameRGB, this->buffer, PIX_FMT_RGB32, width, height);

    struct SwsContext* scConvertContext = sws_getContext(this->avFormatContext->streams[this->videoIndex]->codec->width,
                                                         this->avFormatContext->streams[this->videoIndex]->codec->height,
                                                         this->avFormatContext->streams[this->videoIndex]->codec->pix_fmt,
                                                         width, height, PIX_FMT_RGB32,
                                                         SWS_BICUBIC, NULL, NULL, NULL);
    if (scConvertContext == NULL)
    {
        throw UnableToGetSwScaleContext;
    }

    sws_scale(scConvertContext, this->avFrame->data, this->avFrame->linesize, 0,
              this->avFormatContext->streams[this->videoIndex]->codec->height,
              this->avFrameRGB->data, this->avFrameRGB->linesize);

    return this->avFrameRGB->data[0];
}

void MovieFile::allocateFrame()
{
    this->avFrame = avcodec_alloc_frame();
    if (this->avFrame == NULL)
    {
        throw std::bad_alloc();
    }

    this->frameAllocated = true;
}

void MovieFile::readFrame()
{
    if (!this->frameAllocated)
    {
        this->allocateFrame();
    }

    int gotFrame;
    AVPacket packet;
    while (av_read_frame(this->avFormatContext, &packet) >= 0)
    {
        if (packet.stream_index == this->videoIndex)
        {
            avcodec_decode_video2(this->avFormatContext->streams[videoIndex]->codec, this->avFrame,
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
    av_free(this->avFrame);
    this->frameAllocated = false;
}
