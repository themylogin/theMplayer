#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <QImage>
#include <QProcess>
#include <QString>

#include "Movie.h"

Movie::Movie(QString filename, QString title, int thumbnailWidth, int thumbnailHeight)
        : filename(filename), title(title)
{
    QString thumbnailsDir = QDir::homePath() + "/.thumbnails";
    if (!QDir(thumbnailsDir).exists())
    {
        QDir(thumbnailsDir).mkdir(thumbnailsDir);
    }

    QString theMplayerThumbnailsDir = thumbnailsDir + "/theMplayer";
    if (!QDir(theMplayerThumbnailsDir).exists())
    {
        QDir(theMplayerThumbnailsDir).mkdir(theMplayerThumbnailsDir);
    }

    QString cacheFilename = theMplayerThumbnailsDir + "/" + QString(QCryptographicHash::hash(
        (filename + "#" + QString::number(thumbnailWidth) + "#" + QString::number(thumbnailHeight)).toUtf8(),
        QCryptographicHash::Md5).toHex()) + ".jpg";
    if (QFile::exists(cacheFilename))
    {
        thumbnailBuf = NULL;
        thumbnail = new QImage(cacheFilename);
    }
    else
    {
        movieFile = new MovieFile(filename);

        thumbnailHeight = -1;
        thumbnailBuf = movieFile->getRGB32Thumbnail(thumbnailWidth, thumbnailHeight);
        thumbnail = new QImage(thumbnailBuf, thumbnailWidth, thumbnailHeight, QImage::Format_ARGB32);

        delete movieFile;

        thumbnail->save(cacheFilename, 0, 85);
    }
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
    if (thumbnailBuf != NULL)
    {
        delete thumbnailBuf;
    }
}
