#ifndef SCROLLABLEGRID_H
#define SCROLLABLEGRID_H

#include <QList>

#include "DrawingDirection.h"
#include "ScrollingDirection.h"

template <class T> class ScrollableGrid
{
    public:
        ScrollableGrid(int cols, int rows, DrawingDirection dd);

        QList <T> list;
        void addItem(T item);
        T itemAt(int col, int row);

        bool scrollingAllowed(ScrollingDirection sd);
        void scroll(ScrollingDirection sd);

    private:
        int cols;
        int rows;
        DrawingDirection dd;        

        int scrolled;
};

#endif // SCROLLABLEGRID_H
