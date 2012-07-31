#ifndef TESTMOVIEGRID_H
#define TESTMOVIEGRID_H

#include <QWidget>

#include "AbstractMovieGrid.h"

class TestMovieGrid : public AbstractMovieGrid, public QWidget
{
    public:
        TestMovieGrid(int _width,                      int _height,
                      int _movieWidth,                 int _movieHeight,
                      int _movieFieldHorizontalMargin, int _movieFieldHorizontalPadding,
                      int _movieFieldVerticalMargin,   int _movieFieldVerticalPadding,
                      QWidget *parent = 0);

    protected:
        void paintEvent(QPaintEvent *pe);
        void draw(int col, int row, int x, int y);
};

#endif // TESTMOVIEGRID_H
