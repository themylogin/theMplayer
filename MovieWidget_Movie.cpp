#include "MovieWidget_Movie.h"

#include <QPainter>

MovieWidget_Movie::MovieWidget_Movie(int width, int height, Movie* movie, QWidget* parent)
    : MovieWidget(width, height, movie->getTitle(), parent)
{
    this->movie = movie;
}

void MovieWidget_Movie::activate()
{
    this->movie->play();
}

void MovieWidget_Movie::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    painter.drawImage(QRect(0,      (height() - this->movie->getThumbnail()->height()) / 2,
                            width(), this->movie->getThumbnail()->height()),
                      *(this->movie->getThumbnail()));

    this->paintText();
    this->paintBorder();
}
