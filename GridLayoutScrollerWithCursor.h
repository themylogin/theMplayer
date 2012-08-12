#ifndef GRIDLAYOUTSCROLLERWITHCURSOR_H
#define GRIDLAYOUTSCROLLERWITHCURSOR_H

#include "GridLayoutScroller.h"

/* GridLayoutScrollerWithCursor adds cursor functionality to GridLayoutScroller: cursor can be moved
 * in four directions, scrolling the grid if necessary.
 */
class GridLayoutScrollerWithCursor : public GridLayoutScroller
{
    public:
        GridLayoutScrollerWithCursor(GridLayout* gridLayout, GridLayoutDrawingDirection drawingDirection);

        bool up(int items);
        bool down(int items);
        bool left(int items);
        bool right(int items);

        bool isCurrent(int col, int row);

    protected:
        int currentItem;
        bool setCurrentItem(int newCurrentItem, int items);
};

#endif // GRIDLAYOUTSCROLLERWITHCURSOR_H
