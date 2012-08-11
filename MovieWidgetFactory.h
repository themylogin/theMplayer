#ifndef MOVIEWIDGETFACTORY_H
#define MOVIEWIDGETFACTORY_H

#include "MovieWidget.h"

class Movie;

class QDir;
#include <QMutex>
class QString;
#include <QThread>
class QWidget;

class MovieWidgetFactory : public QThread
{
    Q_OBJECT

    public:
        MovieWidgetFactory(QString directory, int thumbnailWidth, int thumbnailHeight);

    protected:
        void run();

    private:
        QString directory;
        int thumbnailWidth, thumbnailHeight;

        int hasVideoFiles(QString directory);
        QString getFirstVideoFile(QString directory);

        bool isVideoFile(QString filename);

        QString makeTitle(QString filename);

        static QMutex movieFileMutex;

    signals:
        void readyMovieWidget_Movie(Movie* );
        void readyMovieWidget_Directory(QString, QString);
};

#endif // MOVIEWIDGETFACTORY_H
