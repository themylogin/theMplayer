#include <QCoreApplication>
#include <QKeyEvent>
#include <QPainter>
#include <QPen>

#include "MovieWidgetFactory.h"
#include "MovieWidget.h"
#include "MovieWidget_Directory.h"
#include "MovieWidget_Movie.h"
#include "MovieGrid.h"
#include "Movie.h"
#include "ScrollableGridWithCursor.h"

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

    movieWidgetFactory = new MovieWidgetFactory(directory, this->movieWidth, this->movieHeight);
    connect(movieWidgetFactory, SIGNAL(readyMovieWidget_Movie(Movie*)), this, SLOT(addMovieWidget_Movie(Movie*)));
    connect(movieWidgetFactory, SIGNAL(readyMovieWidget_Directory(QString, QString)), this, SLOT(addMovieWidget_Directory(QString, QString)));
    movieWidgetFactory->start();

    drawingDirection = dd;
    scrollableGrid = new ScrollableGridWithCursor(cols, rows, drawingDirection);
}

void MovieGrid::paintEvent(QPaintEvent *pe)
{
    if (pe->region().rectCount() != 1)
    {
        // skip recursive repaints
        return;
    }

    for (int i = 0; i < this->movieWidgets.size(); i++)
    {
        this->movieWidgets[i]->hide();
    }

    drawAll(drawingDirection);
}

void MovieGrid::draw(int col, int row, int x, int y)
{
    QPainter painter(this);

    int index = this->scrollableGrid->indexAt(col, row);
    if (index < this->movieWidgets.size())
    {
        MovieWidget* w = this->movieWidgets[index];
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
            this->scrollableGrid->down(this->movieWidgets.length());
            update();
            break;
        case Qt::Key_Right:
            this->scrollableGrid->right(this->movieWidgets.length());
            update();
            break;
        case Qt::Key_Up:
            this->scrollableGrid->up(this->movieWidgets.length());
            update();
            break;
        case Qt::Key_Left:
            this->scrollableGrid->left(this->movieWidgets.length());
            update();
            break;

        case Qt::Key_Return:
            this->movieWidgets[this->scrollableGrid->currentIndex()]->activate();
            break;
    }
}

void MovieGrid::addMovieWidget(MovieWidget* movieWidget)
{
    QString title = movieWidget->windowTitle();

    bool inserted = false;
    for (int i = 0; i < this->movieWidgets.size(); i++)
    {
        if (title <= this->movieWidgets[i]->windowTitle())
        {
            this->movieWidgets.insert(i, movieWidget);
            inserted = true;
            break;
        }
    }
    if (!inserted)
    {
        this->movieWidgets.append(movieWidget);
    }

    update();
}

void MovieGrid::addMovieWidget_Directory(QString directory, QString title)
{
    this->addMovieWidget(new MovieWidget_Directory(
                            this->movieWidth, this->movieHeight,
                            title,
                            new MovieGrid(
                                this->AbstractMovieGrid::width,   this->AbstractMovieGrid::height,
                                this->movieWidth,                 this->movieHeight,
                                this->movieFieldHorizontalMargin, this->movieFieldHorizontalPadding,
                                this->movieFieldVerticalMargin,   this->movieFieldVerticalPadding,
                                directory,
                                this->drawingDirection,
                                (QWidget*)this->parent()),
                            this));
}

void MovieGrid::addMovieWidget_Movie(Movie* movie)
{
    this->addMovieWidget(new MovieWidget_Movie(this->movieWidth, this->movieHeight, movie, this));
}

void MovieGrid::scrollForward()
{
    if (scrollableGrid->scrollingAllowed(Forward, this->movieWidgets.length()))
    {
        scrollableGrid->scroll(Forward);
        update();
    }
}

void MovieGrid::scrollBackward()
{
    if (scrollableGrid->scrollingAllowed(Backward, this->movieWidgets.length()))
    {
        scrollableGrid->scroll(Backward);
        update();
    }
}
