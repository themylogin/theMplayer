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

        QImage text;
        QImage image;
        QFuture<QImage> futureImage;
        QFutureWatcher<QImage> futureImageWatcher;
        QString cacheFilename;

        QMap<int, QImage> scaledTexts;
        QMap<int, QImage> scaledImages;

        QProcess process;

    private slots:
        void futureImageReady();
};

#endif // MOVIE_H
