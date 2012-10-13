#ifndef MOVIEFILE_H
#define MOVIEFILE_H

extern "C"
{
    #define __STDC_CONSTANT_MACROS
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
}

#include <QString>

class MovieFile
{
    enum MovieFileException
    {
        UnableToOpenFile,
        UnableToFindStreamInformation,
        UnableToFindVideoStream,
        UnableToFindDecoder,
        UnableToOpenDecoder,
        UnableToGetSwScaleContext,
        NotAVideoFile
    };

    public:
        MovieFile(QString filename);
        ~MovieFile();

        int64_t getDuration() const;
        uint8_t* getRGB32Thumbnail(int& width, int& height);

    private:
        static bool             avRegistered;

        AVFormatContext*        avFormatContext;
        AVCodec*                avCodec;
        bool                    avCodecOpen;
        int                     videoIndex;

        AVFrame*                avFrame;
        AVFrame*                avFrameRGB;
        uint8_t*                buffer;
        bool                    frameAllocated;

        void allocateFrame();
        void readFrame();
        void freeFrame();
};

#endif // MOVIEFILE_H
