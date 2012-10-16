#ifndef MOVIE_H
#define MOVIE_H

#include <QFuture>
#include <QFutureWatcher>
#include <QMap>
#include <QProcess>
#include <QString>
#include <QWidget>

#include "MovieCollectionItem.h"

class Movie : public MovieCollectionItem
{
    Q_OBJECT

    public:
        explicit Movie(QString title, QString path, QWidget* parent = 0);

    protected:
        void paintEvent(QPaintEvent* event);

        void activate();

    private:
        QString title;
        QString path;

        int supposedWidth;
        int supposedHeight;

        QImage image;
        QFuture<QImage> futureImage;
        QFutureWatcher<QImage> futureImageWatcher;
        QString cacheFilename;

        QMap<int, QPixmap> cachedRepresentations;

        QProcess process;

    private slots:
        void futureImageReadyFromCache();
        void futureImageReady();
};

#endif // MOVIE_H
