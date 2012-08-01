#ifndef SCROLLABLEGRID_H
#define SCROLLABLEGRID_H

#include "DrawingDirection.h"
#include "ScrollingDirection.h"

class ScrollableGrid
{
    public:
        ScrollableGrid(int cols, int rows, DrawingDirection dd);

        int indexAt(int col, int row);

        bool scrollingAllowed(ScrollingDirection sd, int items);
        void scroll(ScrollingDirection sd);

    protected:
        int cols;
        int rows;
        DrawingDirection dd;        

        int scrolled;
};

#endif // SCROLLABLEGRID_H
