#include "ScrollableGrid.h"

ScrollableGrid::ScrollableGrid(int cols, int rows, DrawingDirection dd)
{
    this->cols = cols;
    this->rows = rows;
    this->dd   = dd;

    this->scrolled = 0;
}

int ScrollableGrid::indexAt(int col, int row)
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

bool ScrollableGrid::scrollingAllowed(ScrollingDirection sd, int items)
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
                    return scrolled + 1 < items / cols;
                    break;

                case Horizontal:
                    return scrolled + 1 < items / rows;
                    break;
            }
            break;
    }

    return false;
}

void ScrollableGrid::scroll(ScrollingDirection sd)
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
