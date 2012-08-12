#include "GridLayoutScroller.h"

GridLayoutScroller::GridLayoutScroller(GridLayout* gridLayout, GridLayoutDrawingDirection drawingDirection)
{
    this->gridLayout = gridLayout;
    this->drawingDirection = drawingDirection;

    this->scrolled = 0;
}

bool GridLayoutScroller::scrollingAllowed(GridLayoutScrollingDirection scrollingDirection, int items)
{
    switch (scrollingDirection)
    {
        case Backward:
            if (scrolled == 0)
            {
                return false;
            }
            else
            {
                return true;
            }
            break;

        case Forward:
            switch (this->drawingDirection)
            {
                case Vertical:
                    return scrolled + 1 < items / this->gridLayout->getCols();
                    break;

                case Horizontal:
                    return scrolled + 1 < items / this->gridLayout->getRows();
                    break;
            }
            break;
    }

    return false;
}

void GridLayoutScroller::scroll(GridLayoutScrollingDirection scrollingDirection)
{
    switch (scrollingDirection)
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

int GridLayoutScroller::indexAt(int col, int row)
{
    switch (this->drawingDirection)
    {
        case Vertical:
            return (row + this->scrolled) * this->gridLayout->getCols() + col;
            break;

        case Horizontal:
            return (col + this->scrolled) * this->gridLayout->getRows() + row;
            break;
    }

    return -1;
}
