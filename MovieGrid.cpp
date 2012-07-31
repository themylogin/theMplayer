#include <QKeyEvent>
#include <QPainter>
#include <QPen>

#include "MovieWidgetFactoryThread.h"
#include "MovieWidget.h"
#include "MovieWidget_Movie.h"
#include "MovieGrid.h"
#include "Movie.h"
#include "ScrollableGridWithCursor.cpp"

MovieGrid::MovieGrid(int _width,                      int _height,
                     int _movieWidth,                 int _movieHeight,
                     int _movieFieldHorizontalMargin, int _movieFieldHorizontalPadding,
                     int _movieFieldVerticalMargin,   int _movieFieldVerticalPadding,
                     QString directory,
                     DrawingDirection dd,
                     QWidget *parent)
    : QWidget(parent), AbstractMovieGrid(_width,                      _height,
                                         _movieWidth,                 _movieHeight,
                                         _movieFieldHorizontalMargin, _movieFieldHorizontalPadding,
                                         _movieFieldVerticalMargin,   _movieFieldVerticalPadding)
{
    QPalette myPalette = palette();
    myPalette.setColor(backgroundRole(), QColor(0, 0, 0));
    setPalette(myPalette);

    movieFactoryThread = new MovieWidgetFactoryThread(directory, movieWidth, movieHeight);
    connect(movieFactoryThread, SIGNAL(movieCreated(Movie *)), this, SLOT(addMovie(Movie *)));
    movieFactoryThread->start();

    drawingDirection = dd;
    scrollableGrid = new ScrollableGridWithCursor<MovieWidget *>(cols, rows, drawingDirection);
}

void MovieGrid::paintEvent(QPaintEvent *pe)
{
    if (pe->region().rectCount() != 1)
    {
        // skip recursive repaints
        return;
    }

    for (int i = 0; i < scrollableGrid->list.size(); i++)
    {
        scrollableGrid->list.at(i)->hide();
    }

    drawAll(drawingDirection);
}

void MovieGrid::draw(int col, int row, int x, int y)
{
    QPainter painter(this);

    MovieWidget* w = this->scrollableGrid->itemAt(col, row);
    if (w != NULL)
    {
        w->setGeometry(QRect(x, y, w->size().width(), w->size().height()));
        w->show();

        if (this->scrollableGrid->isCurrent(col, row))
        {
            QPen pen(QColor(255, 0, 0));
            pen.setWidth(4);
            painter.setPen(pen);
            painter.drawRect(QRect(x - 2, y - 2, w->size().width() + 4, w->size().height() + 4));
        }
    }
}

void MovieGrid::keyPressEvent(QKeyEvent *ke)
{
    switch (ke->key())
    {
        case Qt::Key_Down:
            this->scrollableGrid->down();
            update();
            break;
        case Qt::Key_Right:
            this->scrollableGrid->right();
            update();
            break;
        case Qt::Key_Up:
            this->scrollableGrid->up();
            update();
            break;
        case Qt::Key_Left:
            this->scrollableGrid->left();
            update();
            break;

        case Qt::Key_Return:
            this->scrollableGrid->getActiveItem()->activate();
            break;
    }
}

void MovieGrid::addMovie(Movie *movie)
{
    scrollableGrid->addItem(new MovieWidget_Movie(this->movieWidth, this->movieHeight, movie, this));
    update();
}

void MovieGrid::scrollForward()
{
    if (scrollableGrid->scrollingAllowed(Forward))
    {
        scrollableGrid->scroll(Forward);
        update();
    }
}

void MovieGrid::scrollBackward()
{
    if (scrollableGrid->scrollingAllowed(Backward))
    {
        scrollableGrid->scroll(Backward);
        update();
    }
}
