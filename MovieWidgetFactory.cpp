#include <QDir>
#include <QString>

#include "MovieWidgetFactory.h"

#include "Movie.h"

QMutex MovieWidgetFactory::movieFileMutex;

MovieWidgetFactory::MovieWidgetFactory(QString directory, int thumbnailWidth, int thumbnailHeight)
{
    this->directory = directory;
    this->thumbnailWidth = thumbnailWidth;
    this->thumbnailHeight = thumbnailHeight;
}

void MovieWidgetFactory::run()
{
    QDir dir(this->directory);
    if (!dir.exists())
    {
        return;
    }

    QStringList dirs = dir.entryList(QDir::Dirs, QDir::Name);
    QStringList files = dir.entryList(QDir::Files, QDir::Name);

    for (int i = 0; i < dirs.size(); ++i)
    {
        if (!dirs.at(i).compare(".") || !dirs.at(i).compare(".."))
        {
            continue;
        }
        int countVideoFiles = this->hasVideoFiles(this->directory + QDir::separator() + dirs.at(i));
        if (countVideoFiles > 0)
        {
            if (countVideoFiles == 1)
            {
                QString videoFile = this->getFirstVideoFile(this->directory + QDir::separator() + dirs.at(i));
                try
                {
                    QMutexLocker lock(&this->movieFileMutex);
                    Movie* movie = new Movie(
                                videoFile,
                                this->makeTitle(dirs.at(i)), this->thumbnailWidth, this->thumbnailHeight);
                    emit readyMovieWidget_Movie(movie);
                }
                catch (...)
                {
                }
            }
            else
            {
                emit readyMovieWidget_Directory(
                            this->directory + QDir::separator() + dirs.at(i),
                            this->makeTitle(dirs.at(i)));
            }
        }
    }

    for (int i = 0; i < files.size(); ++i)
    {
        if (this->isVideoFile(files.at(i)))
        {
            try
            {
                QMutexLocker lock(&this->movieFileMutex);
                Movie* movie = new Movie(
                            this->directory + QDir::separator() + files.at(i),
                            this->makeTitle(files.at(i)), this->thumbnailWidth, this->thumbnailHeight);
                emit readyMovieWidget_Movie(movie);
            }
            catch (...)
            {
            }
        }
    }
}

int MovieWidgetFactory::hasVideoFiles(QString directory)
{
    QDir dir(directory);
    if (!dir.exists())
    {
        return 0;
    }

    int count = 0;
    QStringList dirs = dir.entryList(QDir::Dirs, QDir::Name);
    QStringList files = dir.entryList(QDir::Files, QDir::Name);

    for (int i = 0; i < dirs.size(); ++i)
    {
        if (!dirs.at(i).compare(".") || !dirs.at(i).compare(".."))
        {
            continue;
        }
        count += this->hasVideoFiles(directory + QDir::separator() + dirs.at(i));
    }

    for (int i = 0; i < files.size(); ++i)
    {
        if (this->isVideoFile(files.at(i)))
        {
            count++;
        }
    }

    return count;
}

QString MovieWidgetFactory::getFirstVideoFile(QString directory)
{
    QDir dir(directory);
    if (!dir.exists())
    {
        return 0;
    }

    int count = 0;
    QStringList dirs = dir.entryList(QDir::Dirs, QDir::Name);
    QStringList files = dir.entryList(QDir::Files, QDir::Name);

    for (int i = 0; i < dirs.size(); ++i)
    {
        if (!dirs.at(i).compare(".") || !dirs.at(i).compare(".."))
        {
            continue;
        }
        QString videoFile = this->getFirstVideoFile(directory + QDir::separator() + dirs.at(i));
        if (videoFile != "")
        {
            return videoFile;
        }
    }

    for (int i = 0; i < files.size(); ++i)
    {
        if (this->isVideoFile(files.at(i)))
        {
            return directory + QDir::separator() + files.at(i);
        }
    }

    return "";
}

bool MovieWidgetFactory::isVideoFile(QString filename)
{
    QString cmp = filename.toLower();
    return cmp.endsWith(".avi") || cmp.endsWith(".mkv");
}

QString MovieWidgetFactory::makeTitle(QString filename)
{
    QString title = filename;
    title.replace(QRegExp("^/"), QString(""));
    title.replace(QRegExp("\\.[a-zA-Z0-9]*$"), QString(""));
    title.replace(QRegExp("\\.|_"), QString(" "));
    title.replace(QString("/"), QString(" / "));
    return title;
}
