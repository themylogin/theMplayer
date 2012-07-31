#ifndef SCROLLABLEGRID_CPP
#define SCROLLABLEGRID_CPP

#include "ScrollableGrid.h"

template <class T> ScrollableGrid<T>::ScrollableGrid(int cols, int rows, DrawingDirection dd)
        : cols(cols), rows(rows), dd(dd)
{
    scrolled = 0;
}

template <class T> void ScrollableGrid<T>::addItem(T item)
{
    list.append(item);
}

template <class T> T ScrollableGrid<T>::itemAt(int col, int row)
{
    int i;
    switch (dd)
    {
        case Vertical:
            i = (row + scrolled) * cols + col;
            break;

        case Horizontal:
            i = (col + scrolled) * rows + row;
            break;

        default:
            i = 0;
            break;
    }

    if (i < list.size())
    {
        return list.at(i);
    }

    return NULL;
}

template <class T> bool ScrollableGrid<T>::scrollingAllowed(ScrollingDirection sd)
{
    switch (sd)
    {
        case Backward:
            if (scrolled == 0)
            {
                return false;
            } else {
                return true;
            }
            break;

        case Forward:
            switch (dd)
            {
                case Vertical:
                    return scrolled + 1 < list.size() / cols;
                    break;

                case Horizontal:
                    return scrolled + 1 < list.size() / rows;
                    break;
            }
            break;
    }

    return false;
}

template <class T> void ScrollableGrid<T>::scroll(ScrollingDirection sd)
{
    switch (sd)
    {
        case Backward:
            scrolled--;
            break;

        case Forward:
            scrolled++;
            break;

        default:
            break;
    }
}

#endif // SCROLLABLEGRID_CPP
