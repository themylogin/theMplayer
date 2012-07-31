#ifndef MOVIEWIDGET_H
#define MOVIEWIDGET_H

class Movie;
#include <QImage>
#include <QWidget>

class MovieWidget : public QWidget
{
    Q_OBJECT

    public:
        MovieWidget(Movie *movie, QWidget *parent = 0);
        void activate();

    protected:
        Movie* movie;
        QImage movieTitle;
        void paintEvent(QPaintEvent *pe);
};

#endif // MOVIEWIDGET_H
