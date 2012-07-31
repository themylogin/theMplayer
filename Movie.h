#ifndef MOVIE_H
#define MOVIE_H

class QImage;
#include <QString>

#include "MovieFile.h"

class Movie
{
    public:
        Movie(QString filename, QString title, int thumbnailWidth, int thumbnailHeight);
        ~Movie();
        void play();

        QImage *getThumbnail() const;
        QString getTitle() const;

    private:
        QString filename;
        QString title;

        MovieFile *movieFile;
        uint8_t *thumbnailBuf;
        QImage *thumbnail;
};

#endif // MOVIE_H
