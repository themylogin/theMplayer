#ifndef MOVIEWIDGET_MOVIE_H
#define MOVIEWIDGET_MOVIE_H

#include "Movie.h"
#include "MovieWidget.h"

class MovieWidget_Movie : public MovieWidget
{
    Q_OBJECT

    public:
        MovieWidget_Movie(int width, int height, Movie* movie, QWidget* parent = 0);
        void activate();

    protected:
        Movie* movie;

        void paintEvent(QPaintEvent *pe);
};

#endif // MOVIEWIDGET_MOVIE_H
