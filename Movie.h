#ifndef MOVIE_H
#define MOVIE_H

#include <QMap>
#include <QString>
#include <QWidget>

class Movie : public QWidget
{
    Q_OBJECT

    public:
        explicit Movie(QString title, QString path, QWidget* parent = 0);

    protected:
        void paintEvent(QPaintEvent* event);

    private:
        QString title;
        QString path;

        int supposedWidth;
        int supposedHeight;

        QImage text;
        QImage image;

        QMap<int, QImage> scaledTexts;
        QMap<int, QImage> scaledImages;
};

#endif // MOVIE_H
