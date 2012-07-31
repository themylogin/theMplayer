#include <QPainter>
#include <QSize>

#include "TestMovieGrid.h"

TestMovieGrid::TestMovieGrid(int _width,                      int _height,
                             int _movieWidth,                 int _movieHeight,
                             int _movieFieldHorizontalMargin, int _movieFieldHorizontalPadding,
                             int _movieFieldVerticalMargin,   int _movieFieldVerticalPadding,
                             QWidget *parent)
    : AbstractMovieGrid(_width,                      _height,
                        _movieWidth,                 _movieHeight,
                        _movieFieldHorizontalMargin, _movieFieldHorizontalPadding,
                        _movieFieldVerticalMargin,   _movieFieldVerticalPadding), QWidget(parent)
{
    QSize size(_width, _height);
    setMinimumSize(size);
    setMaximumSize(size);
    setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum));
}

void TestMovieGrid::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    painter.fillRect(0, 0, ((QWidget *)this)->width(), ((QWidget *)this)->height(), QColor(0, 0, 0));

    drawAll(Horizontal);
}

void TestMovieGrid::draw(int col, int row, int x, int y)
{
    QPainter painter(this);

    painter.drawRect(QRect(x, y, getMovieWidth(), getMovieHeight()));
}
