#include <QtGui>
#include "AbstractMovieGrid.h"

AbstractMovieGrid::AbstractMovieGrid(int _width,                      int _height,
                                     int _movieWidth,                 int _movieHeight,
                                     int _movieFieldHorizontalMargin, int _movieFieldHorizontalPadding,
                                     int _movieFieldVerticalMargin,   int _movieFieldVerticalPadding)
    : width(_width),                                           height(_height),
      movieWidth(_movieWidth),                                 movieHeight(_movieHeight),
      movieFieldHorizontalMargin(_movieFieldHorizontalMargin), movieFieldHorizontalPadding(_movieFieldHorizontalPadding),
      movieFieldVerticalMargin(_movieFieldVerticalMargin),     movieFieldVerticalPadding(_movieFieldVerticalPadding)
{
    calculateDimensions();
    correctMargins();
}

void AbstractMovieGrid::calculateDimensions()
{
    cols = (width - 2 * movieFieldHorizontalMargin + movieFieldHorizontalPadding) / (movieWidth + movieFieldHorizontalPadding);
    rows = (height - 2 * movieFieldVerticalMargin + movieFieldVerticalPadding) / (movieHeight + movieFieldVerticalPadding);
}

void AbstractMovieGrid::correctMargins()
{
    movieFieldHorizontalMargin = (width - cols * (movieWidth + movieFieldHorizontalPadding) + movieFieldHorizontalPadding) / 2;
    movieFieldVerticalMargin = (height - rows * (movieHeight + movieFieldVerticalPadding) + movieFieldVerticalPadding) / 2;
}

void AbstractMovieGrid::drawAll(DrawingDirection dd)
{
    switch (dd)
    {
        case Horizontal:
            for (int row = 0; row < rows; row++)
            {
                for (int col = 0; col < cols; col++)
                {
                    callDrawer(col, row);
                }
            }
            break;
        case Vertical:
            for (int col = 0; col < cols; col++)
            {
                for (int row = 0; row < rows; row++)
                {
                    callDrawer(col, row);
                }
            }
            break;
    }
}

void AbstractMovieGrid::callDrawer(int col, int row)
{
    int x = movieFieldHorizontalMargin + col * (movieWidth + movieFieldHorizontalPadding);
    int y = movieFieldVerticalMargin + row * (movieHeight + movieFieldVerticalPadding);
    draw(col, row, x, y);
}

int AbstractMovieGrid::getWidth() const
{
    return width;
}

int AbstractMovieGrid::getHeight() const
{
    return height;
}

int AbstractMovieGrid::getMovieWidth() const
{
    return movieWidth;
}

int AbstractMovieGrid::getMovieHeight() const
{
    return movieHeight;
}

int AbstractMovieGrid::getMovieFieldHorizontalMargin() const
{
    return movieFieldHorizontalMargin;
}

int AbstractMovieGrid::getMovieFieldHorizontalPadding() const
{
    return movieFieldHorizontalPadding;
}

int AbstractMovieGrid::getMovieFieldVerticalMargin() const
{
    return movieFieldVerticalMargin;
}

int AbstractMovieGrid::getMovieFieldVerticalPadding() const
{
    return movieFieldVerticalPadding;
}

void AbstractMovieGrid::setWidth(int value)
{
    width = value;
    calculateDimensions();
    correctMargins();
}

void AbstractMovieGrid::setHeight(int value)
{
    height = value;
    calculateDimensions();
    correctMargins();
}

void AbstractMovieGrid::setMovieWidth(int value)
{
    movieWidth = value;
    calculateDimensions();
    correctMargins();
}

void AbstractMovieGrid::setMovieHeight(int value)
{
    movieHeight = value;
    calculateDimensions();
    correctMargins();
}

void AbstractMovieGrid::setMovieFieldHorizontalMargin(int value)
{
    movieFieldHorizontalMargin = value;
    calculateDimensions();
    correctMargins();
}

void AbstractMovieGrid::setMovieFieldHorizontalPadding(int value)
{
    movieFieldHorizontalPadding = value;
    calculateDimensions();
    correctMargins();
}

void AbstractMovieGrid::setMovieFieldVerticalMargin(int value)
{
    movieFieldVerticalMargin = value;
    calculateDimensions();
    correctMargins();
}

void AbstractMovieGrid::setMovieFieldVerticalPadding(int value)
{
    movieFieldVerticalPadding = value;
    calculateDimensions();
    correctMargins();
}
