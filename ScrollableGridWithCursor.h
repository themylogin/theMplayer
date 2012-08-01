#ifndef SCROLLABLEGRIDWITHCURSOR_H
#define SCROLLABLEGRIDWITHCURSOR_H

#include "ScrollableGrid.h"

class ScrollableGridWithCursor : public ScrollableGrid
{
    public:
        ScrollableGridWithCursor(int cols, int rows, DrawingDirection dd);

        bool up(int items);
        bool down(int items);
        bool left(int items);
        bool right(int items);

        int currentIndex();
        bool isCurrent(int col, int row);

    protected:
        int currentItem;
        bool setCurrentItem(int newCurrentItem, int items);
};

#endif // SCROLLABLEGRIDWITHCURSOR_H
