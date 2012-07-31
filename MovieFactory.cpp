#include <QDir>
#include <QString>

#include "MovieFactory.h"

void MovieFactory::createMovies(QString directoryName, int thumbnailWidth, int thumbnailHeight, bool _firstCall)
{
    QDir dir(directoryName);
    if (!dir.exists())
    {
        throw NoSuchDirectory;
    }
    if (_firstCall)
    {
        stripFromTitles = dir.absolutePath();
    }

    if (dir.exists(QString("VIDEO_TS.VOB")))
    {
        // Is a DVD Directory
        createDVDMovie(dir);
    } else {
        QStringList dirs = dir.entryList(QDir::Dirs, QDir::Name);
        QStringList files = dir.entryList(QDir::Files, QDir::Name);

        for (int i = 0; i < dirs.size(); ++i)
        {            
            if (!dirs.at(i).compare(".") || !dirs.at(i).compare(".."))
            {
                continue;
            }
            QString subdirectoryName = directoryName + QDir::separator() + dirs.at(i);
            MovieFactory::createMovies(subdirectoryName, thumbnailWidth, thumbnailHeight, false);
        }

        for (int i = 0; i < files.size(); ++i)
        {
            QString fileName = directoryName + QDir::separator() + files.at(i);

            try
            {
                Movie *movie = new Movie(fileName, makeTitle(fileName), thumbnailWidth, thumbnailHeight);
                emit movieCreated(movie);
            } catch (...) {
            }
        }
    }
}

void MovieFactory::createDVDMovie(QDir directory)
{
}

QString MovieFactory::makeTitle(QString absoluteFilePath)
{
    QString title = absoluteFilePath.replace(stripFromTitles, QString(""));
    title.replace(QRegExp("^/"), QString(""));
    title.replace(QRegExp("\\.[a-zA-Z0-9]*$"), QString(""));
    title.replace(QRegExp("\\.|_"), QString(" "));
    title.replace(QString("/"), QString(" / "));
    return title;
}
