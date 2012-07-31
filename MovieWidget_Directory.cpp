#include "MovieWidget_Directory.h"

#include <QPainter>

MovieWidget_Directory::MovieWidget_Directory(int width, int height, QString title, MovieGrid* grid, QWidget* parent)
    : MovieWidget(width, height, title, parent)
{
    this->grid = grid;
    setWindowTitle(title);
}

void MovieWidget_Directory::activate()
{
    this->grid->showFullScreen();
}

void MovieWidget_Directory::paintEvent(QPaintEvent *pe)
{
    /*QPainter painter(this);
    painter.drawImage(QRect(0,      (height() - this->movie->getThumbnail()->height()) / 2,
                            width(), this->movie->getThumbnail()->height()),
                      *(this->movie->getThumbnail()));*/

    this->paintText();
    this->paintBorder();
}
