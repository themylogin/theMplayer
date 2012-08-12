#include "GridLayoutScrollerWithCursor.h"

GridLayoutScrollerWithCursor::GridLayoutScrollerWithCursor(GridLayout* gridLayout, GridLayoutDrawingDirection drawingDirection)
    : GridLayoutScroller(gridLayout, drawingDirection)
{
    this->currentItem = 0;
}

bool GridLayoutScrollerWithCursor::up(int items)
{
    switch (this->drawingDirection)
    {
        case Vertical:
            return this->setCurrentItem(this->currentItem - this->gridLayout->getCols(), items);
            break;

        case Horizontal:
            return this->setCurrentItem(this->currentItem - 1, items);
            break;
    }

    return false;
}

bool GridLayoutScrollerWithCursor::down(int items)
{
    switch (this->drawingDirection)
    {
        case Vertical:
            return this->setCurrentItem(this->currentItem + this->gridLayout->getCols(), items);
            break;

        case Horizontal:
            return this->setCurrentItem(this->currentItem + 1, items);
            break;
    }

    return false;
}

bool GridLayoutScrollerWithCursor::left(int items)
{
    switch (this->drawingDirection)
    {
        case Vertical:
            return this->setCurrentItem(this->currentItem - 1, items);
            break;

        case Horizontal:
            return this->setCurrentItem(this->currentItem - this->gridLayout->getRows(), items);
            break;
    }

    return false;
}

bool GridLayoutScrollerWithCursor::right(int items)
{
    switch (this->drawingDirection)
    {
        case Vertical:
            return this->setCurrentItem(this->currentItem + 1, items);
            break;

        case Horizontal:
            return this->setCurrentItem(this->currentItem + this->gridLayout->getRows(), items);
            break;
    }

    return false;
}

bool GridLayoutScrollerWithCursor::isCurrent(int col, int row)
{
    return this->indexAt(col, row) == this->currentItem;
}

bool GridLayoutScrollerWithCursor::setCurrentItem(int newCurrentItem, int items)
{
    if (newCurrentItem >= 0 && newCurrentItem < items)
    {
        this->currentItem = newCurrentItem;

        switch (this->drawingDirection)
        {
            case Vertical:
                while (this->currentItem < this->scrolled * this->gridLayout->getCols())
                {
                    this->scrolled--;
                }
                while (this->currentItem >= (this->scrolled + this->gridLayout->getRows()) * this->gridLayout->getCols())
                {
                    this->scrolled++;
                }
                break;

            case Horizontal:
                while (this->currentItem < this->scrolled * this->gridLayout->getRows())
                {
                    this->scrolled--;
                }
                while (this->currentItem >= (this->scrolled + this->gridLayout->getCols()) * this->gridLayout->getRows())
                {
                    this->scrolled++;
                }
                break;
        }

        return true;
    }
    else
    {
        return false;
    }
}
