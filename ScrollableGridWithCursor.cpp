#include "ScrollableGridWithCursor.h"

ScrollableGridWithCursor::ScrollableGridWithCursor(int cols, int rows, DrawingDirection dd)
    : ScrollableGrid(cols, rows, dd)
{
    this->currentItem = 0;
}

bool ScrollableGridWithCursor::up(int items)
{
    switch (this->dd)
    {
        case Vertical:
            return this->setCurrentItem(this->currentItem - this->cols, items);
            break;

        case Horizontal:
            return this->setCurrentItem(this->currentItem - 1, items);
            break;
    }

    return false;
}

bool ScrollableGridWithCursor::down(int items)
{
    switch (this->dd)
    {
        case Vertical:
            return this->setCurrentItem(this->currentItem + this->cols, items);
            break;

        case Horizontal:
            return this->setCurrentItem(this->currentItem + 1, items);
            break;
    }

    return false;
}

bool ScrollableGridWithCursor::left(int items)
{
    switch (this->dd)
    {
        case Vertical:
            return this->setCurrentItem(this->currentItem - 1, items);
            break;

        case Horizontal:
            return this->setCurrentItem(this->currentItem - this->rows, items);
            break;
    }

    return false;
}

bool ScrollableGridWithCursor::right(int items)
{
    switch (this->dd)
    {
        case Vertical:
            return this->setCurrentItem(this->currentItem + 1, items);
            break;

        case Horizontal:
            return this->setCurrentItem(this->currentItem + this->rows, items);
            break;
    }

    return false;
}

int ScrollableGridWithCursor::currentIndex()
{
    return this->currentItem;
}

bool ScrollableGridWithCursor::isCurrent(int col, int row)
{
    return this->indexAt(col, row) == this->currentItem;
}

bool ScrollableGridWithCursor::setCurrentItem(int newCurrentItem, int items)
{
    if (newCurrentItem >= 0 && newCurrentItem < items)
    {
        this->currentItem = newCurrentItem;

        switch (this->dd)
        {
            case Vertical:
                while (this->currentItem < this->scrolled * this->cols)
                {
                    this->scrolled--;
                }
                while (this->currentItem >= (this->scrolled + this->rows) * this->cols)
                {
                    this->scrolled++;
                }
                break;

            case Horizontal:
                while (this->currentItem < this->scrolled * this->rows)
                {
                    this->scrolled--;
                }
                while (this->currentItem >= (this->scrolled + this->cols) * this->rows)
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
