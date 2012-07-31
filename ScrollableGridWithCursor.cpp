#include "ScrollableGridWithCursor.h"

template<class T>
ScrollableGridWithCursor<T>::ScrollableGridWithCursor(int cols, int rows, DrawingDirection dd)
    : ScrollableGrid<T>(cols, rows, dd)
{
    this->currentItem = 0;
}

template<class T>
bool ScrollableGridWithCursor<T>::up()
{
    switch (this->dd)
    {
        case Vertical:
            return this->setCurrentItem(this->currentItem - this->cols);
            break;

        case Horizontal:
            return this->setCurrentItem(this->currentItem - 1);
            break;
    }

    return false;
}

template<class T>
bool ScrollableGridWithCursor<T>::down()
{
    switch (this->dd)
    {
        case Vertical:
            return this->setCurrentItem(this->currentItem + this->cols);
            break;

        case Horizontal:
            return this->setCurrentItem(this->currentItem + 1);
            break;
    }

    return false;
}

template<class T>
bool ScrollableGridWithCursor<T>::left()
{
    switch (this->dd)
    {
        case Vertical:
            return this->setCurrentItem(this->currentItem - 1);
            break;

        case Horizontal:
            return this->setCurrentItem(this->currentItem - this->rows);
            break;
    }

    return false;
}

template<class T>
bool ScrollableGridWithCursor<T>::right()
{
    switch (this->dd)
    {
        case Vertical:
            return this->setCurrentItem(this->currentItem + 1);
            break;

        case Horizontal:
            return this->setCurrentItem(this->currentItem + this->rows);
            break;
    }

    return false;
}

template<class T>
bool ScrollableGridWithCursor<T>::isCurrent(int col, int row)
{
    return this->indexAt(col, row) == this->currentItem;
}

template<class T>
bool ScrollableGridWithCursor<T>::setCurrentItem(int newCurrentItem)
{
    if (newCurrentItem >= 0 && newCurrentItem < this->list.length())
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
