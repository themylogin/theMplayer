#ifndef SCROLLABLEGRID_H
#define SCROLLABLEGRID_H

#include "GridLayout.h"
#include "GridLayoutDrawingDirection.h"
#include "GridLayoutScrollingDirection.h"

/* GridLayoutScroller is used when amount of elements in a GridLayout exceedes cols * rows;
 * then, GridLayout represents only visible part of the grid, which can be higher (when
 * drawingDirection == Vertical) or wider (when drawingDirection == Horizontal).
 * GridLayoutScroller can tell if scrolling (Forward or Backward) is possible, scroll
 * and calculate index in 1D-array (staring from 0), representing elements of GridLayout,
 * for each col and row of it.
 */
class GridLayoutScroller
{
    public:
        GridLayoutScroller(GridLayout* gridLayout, GridLayoutDrawingDirection drawingDirection);

        bool scrollingAllowed(GridLayoutScrollingDirection scrollingDirection, int items);
        void scroll(GridLayoutScrollingDirection scrollingDirection);

        int indexAt(int col, int row);

    protected:
        GridLayout* gridLayout;
        GridLayoutDrawingDirection drawingDirection;

        int scrolled;
};

#endif // SCROLLABLEGRID_H
