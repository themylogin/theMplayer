#ifndef MOVIEWIDGET_DIRECTORY_H
#define MOVIEWIDGET_DIRECTORY_H

#include "MovieGrid.h"
#include "MovieWidget.h"

#include <QString>

class MovieWidget_Directory : public MovieWidget
{
    Q_OBJECT

    public:
        MovieWidget_Directory(int width, int height, QString title, MovieGrid* grid, QWidget* parent = 0);
        void activate();

    protected:
        MovieGrid* grid;

        void paintEvent(QPaintEvent *pe);
};

#endif // MOVIEWIDGET_DIRECTORY_H
