#include <QImage>
#include <QProcess>
#include <QString>

#include "Movie.h"

Movie::Movie(QString filename, QString title, int thumbnailWidth, int thumbnailHeight)
        : filename(filename), title(title)
{
    movieFile = new MovieFile(filename);

    thumbnailHeight = -1;
    thumbnailBuf = movieFile->getRGB32Thumbnail(thumbnailWidth, thumbnailHeight);
    thumbnail = new QImage(thumbnailBuf, thumbnailWidth, thumbnailHeight, QImage::Format_ARGB32);

    delete movieFile;
}

QImage *Movie::getThumbnail() const
{
    return thumbnail;
}

QString Movie::getTitle() const
{
    return title;
}

void Movie::play()
{
    QString program = "mplayer";
    QStringList arguments;
    arguments << "-fs" << filename;

    QProcess *mplayer = new QProcess;
    mplayer->start(program, arguments);
}

Movie::~Movie()
{
    delete thumbnail;
    delete thumbnailBuf;
}
