#ifndef MOVIEWIDGET_H
#define MOVIEWIDGET_H

class Movie;
#include <QWidget>

class MovieWidget : public QWidget
{
    Q_OBJECT

    public:
        MovieWidget(Movie *movie, QWidget *parent = 0);
        void activate();

    protected:
        Movie* movie;
        void paintEvent(QPaintEvent *pe);
};

#endif // MOVIEWIDGET_H
