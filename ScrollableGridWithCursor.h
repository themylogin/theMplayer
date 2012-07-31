#ifndef SCROLLABLEGRIDWITHCURSOR_H
#define SCROLLABLEGRIDWITHCURSOR_H

#include "ScrollableGrid.cpp"

template<class T>
class ScrollableGridWithCursor : public ScrollableGrid<T>
{
    public:
        ScrollableGridWithCursor(int cols, int rows, DrawingDirection dd);

        bool up();
        bool down();
        bool left();
        bool right();

        bool isCurrent(int col, int row);

    protected:
        int currentItem;
        bool setCurrentItem(int newCurrentItem);
};

#endif // SCROLLABLEGRIDWITHCURSOR_H
