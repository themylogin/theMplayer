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
    int i = indexAt(col, row);
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

template<class T>
int ScrollableGrid<T>::indexAt(int col, int row)
{
    switch (this->dd)
    {
        case Vertical:
            return (row + this->scrolled) * this->cols + col;
            break;

        case Horizontal:
            return (col + this->scrolled) * this->rows + row;
            break;
    }

    return 0;
}

#endif // SCROLLABLEGRID_CPP
