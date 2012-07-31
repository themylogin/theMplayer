#ifndef ABSTRACTMOVIEGRID_H
#define ABSTRACTMOVIEGRID_H

#include "DrawingDirection.h"

class AbstractMovieGrid
{
    public:
        AbstractMovieGrid(int _width,                      int _height,
                          int _movieWidth,                 int _movieHeight,
                          int _movieFieldHorizontalMargin, int _movieFieldHorizontalPadding,
                          int _movieFieldVerticalMargin,   int _movieFieldVerticalPadding);

        int getWidth() const;
        int getHeight() const;
        int getMovieWidth() const;
        int getMovieHeight() const;
        int getMovieFieldHorizontalMargin() const;
        int getMovieFieldHorizontalPadding() const;
        int getMovieFieldVerticalMargin() const;
        int getMovieFieldVerticalPadding() const;

        void setWidth(int value);
        void setHeight(int value);
        void setMovieWidth(int value);
        void setMovieHeight(int value);
        void setMovieFieldHorizontalMargin(int value);
        void setMovieFieldHorizontalPadding(int value);
        void setMovieFieldVerticalMargin(int value);
        void setMovieFieldVerticalPadding(int value);

        void drawAll(DrawingDirection dd);

    protected:
        int width;
        int height;
        int movieWidth;
        int movieHeight;
        int movieFieldHorizontalMargin;
        int movieFieldHorizontalPadding;
        int movieFieldVerticalMargin;
        int movieFieldVerticalPadding;

        int cols;
        int rows;        
        void calculateDimensions();
        void correctMargins();

        void callDrawer(int col, int row);
        virtual void draw(int col, int row, int x, int y) = 0;

};

#endif // ABSTRACTMOVIEGRID_H
