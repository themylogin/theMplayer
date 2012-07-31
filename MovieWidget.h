#ifndef MOVIEWIDGET_H
#define MOVIEWIDGET_H

class Movie;
#include <QWidget>

class MovieWidget : public QWidget
{
    Q_OBJECT

    public:
        MovieWidget(Movie *movie, QWidget *parent = 0);        

    protected:
        Movie *movie;
        void paintEvent(QPaintEvent *pe);
        void mousePressEvent(QMouseEvent *event);
};

#endif // MOVIEWIDGET_H
