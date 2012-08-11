#include "GridLayout.h"

GridLayout::GridLayout(int gridWidth, int gridHeight, int gridHPadding, int gridVPadding,
                       int elementWidth, int elementHeight, int elementHMargin, int elementVMargin)
{
    this->gridWidth = gridWidth;
    this->gridHeight = gridHeight;
    this->gridHPadding = gridHPadding;
    this->gridVPadding = gridVPadding;

    this->elementWidth = elementWidth;
    this->elementHeight = elementHeight;
    this->elementHMargin = elementHMargin;
    this->elementVMargin = elementVMargin;

    this->calculateDimensions();
    this->correctPaddings();
}

int GridLayout::getGridWidth() const
{
    return this->gridWidth;
}

int GridLayout::getGridHeight() const
{
    return this->gridHeight;
}

int GridLayout::getGridHPadding() const
{
    return this->gridHPadding;
}

int GridLayout::getGridVPadding() const
{
    return this->gridVPadding;
}

int GridLayout::getElementWidth() const
{
    return this->elementWidth;
}

int GridLayout::getElementHeight() const
{
    return this->elementHeight;
}

int GridLayout::getElementHMargin() const
{
    return this->elementHMargin;
}

int GridLayout::getElementVMargin() const
{
    return this->elementVMargin;
}

void GridLayout::setGridWidth(int value)
{
    this->gridWidth = value;
    this->calculateDimensions();
    this->correctPaddings();
}

void GridLayout::setGridHeight(int value)
{
    this->gridHeight = value;
    this->calculateDimensions();
    this->correctPaddings();
}

void GridLayout::setGridHPadding(int value)
{
    this->gridHPadding = value;
    this->calculateDimensions();
    this->correctPaddings();
}

void GridLayout::setGridVPadding(int value)
{
    this->gridVPadding = value;
    this->calculateDimensions();
    this->correctPaddings();
}

void GridLayout::setElementWidth(int value)
{
    this->elementWidth = value;
    this->calculateDimensions();
    this->correctPaddings();
}

void GridLayout::setElementHeight(int value)
{
    this->elementHeight = value;
    this->calculateDimensions();
    this->correctPaddings();
}

void GridLayout::setElementHMargin(int value)
{
    this->elementHMargin = value;
    this->calculateDimensions();
    this->correctPaddings();
}

void GridLayout::setElementVMargin(int value)
{
    this->elementVMargin = value;
    this->calculateDimensions();
    this->correctPaddings();
}

int GridLayout::getCols() const
{
    return this->cols;
}

int GridLayout::getRows() const
{
    return this->rows;
}

int GridLayout::getX(int col) const
{
    return this->gridHPadding + col * (this->elementWidth + this->elementHMargin);
}

int GridLayout::getY(int row) const
{
    return this->gridVPadding + row * (this->elementHeight + this->elementVMargin);
}

void GridLayout::calculateDimensions()
{
    this->cols = (this->gridWidth - 2 * this->gridHPadding + this->elementHMargin) / (this->elementWidth + this->elementHMargin);
    this->rows = (this->gridHeight - 2 * this->gridVPadding + this->elementVMargin) / (this->elementHeight + this->elementVMargin);
}

void GridLayout::correctPaddings()
{
    this->gridHPadding = (this->gridWidth - this->cols * (this->elementWidth + this->elementHMargin) + this->elementHMargin) / 2;
    this->gridVPadding = (this->gridHeight - this->rows * (this->elementHeight + this->elementVMargin) + this->elementVMargin) / 2;
}
