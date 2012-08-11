#ifndef GRIDLAYOUT_H
#define GRIDLAYOUT_H

/* GridLayout calculates arrangement of equal rectangles (each of specified elementWidth and elementHeight)
 * with specified elementHMargin and elementVMargin in a bigger rectangle (of specified gridWidth and gridHeight)
 * with specified gridHPadding and gridVPadding. It calculates the number of cols and rows in
 * this arrangement, calculates corrects margins and paddings and then can calculate a top-left
 * coordinate of each rectangle with specified col and row. Col and row are both indexed from 0.
 *
 *           gridHPadding   elementWidth   elementHMargin
 *                     __  ______________  _
 *                    /  \/              \/ \
 *                    ______________________________________________________________
 *   gridVPadding {  |    ________________   ________________   ________________    |  \
 *                /  |   |                | |                | |                |   |   |
 *                |  |   |                | |                | |                |   |   |
 *                |  |   |                | |                | |                |   |   |
 *  elementHeight |  |   |     (0, 0)     | |     (0, 1)     | |     (0, 2)     |   |   |
 *                |  |   |                | |                | |                |   |   |
 *                |  |   |                | |                | |                |   |   |
 *                \  |   |________________| |________________| |________________|   |   |
 * elementVMargin {  |    ________________   ________________   ________________    |   | gridHeight
 *                   |   |                | |                | |                |   |   |
 *                   |   |                | |                | |                |   |   |
 *                   |   |                | |                | |                |   |   |
 *                   |   |     (1, 0)     | |     (1, 1)     | |     (1, 2)     |   |   |
 *                   |   |                | |                | |                |   |   |
 *                   |   |                | |                | |                |   |   |
 *                   |   |________________| |________________| |________________|   |   |
 *                   |______________________________________________________________|  /
 *
 *                    \____________________________________________________________/
 *                                               gridWidth
 */
class GridLayout
{
    public:
        GridLayout(int gridWidth, int gridHeight, int gridHPadding, int gridVPadding,
                   int elementWidth, int elementHeight, int elementHMargin, int elementVMargin);

        int getGridWidth() const;
        int getGridHeight() const;
        int getGridHPadding() const;
        int getGridVPadding() const;

        int getElementWidth() const;
        int getElementHeight() const;
        int getElementHMargin() const;
        int getElementVMargin() const;

        void setGridWidth(int value);
        void setGridHeight(int value);
        void setGridHPadding(int value);
        void setGridVPadding(int value);

        void setElementWidth(int value);
        void setElementHeight(int value);
        void setElementHMargin(int value);
        void setElementVMargin(int value);

        int getCols() const;
        int getRows() const;

        int getX(int col) const;
        int getY(int row) const;

    private:
        int gridWidth;
        int gridHeight;
        int gridHPadding;
        int gridVPadding;

        int elementWidth;
        int elementHeight;
        int elementHMargin;
        int elementVMargin;

        int cols;
        int rows;        
        void calculateDimensions();
        void correctPaddings();
};

#endif // GRIDLAYOUT_H
