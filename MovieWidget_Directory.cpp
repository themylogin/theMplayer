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
    this->paintText();
    this->paintBorder();
}
