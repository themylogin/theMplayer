#include "MovieList.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QtPropertyAnimation>

MovieList::MovieList(QWidget *parent)
        : QWidget(parent)
{
    movieWidth = 400;
    movieHeight = 300;

    movieHMargin = 10;
    movieVMargin = 10;

    fieldHMargin = 20;
    fieldVMargin = 20;

    QPalette myPalette = palette();
    myPalette.setColor(backgroundRole(), QColor(0, 0, 0));
    setPalette(myPalette);

    _columns = (QApplication::desktop()->geometry().width() - 2 * fieldHMargin + movieHMargin) / (movieWidth + movieHMargin);
    fieldHMargin = (QApplication::desktop()->geometry().width() - _columns * (movieWidth + movieHMargin) - movieHMargin) / 2;
    _rows = (QApplication::desktop()->geometry().height() - 2 * fieldVMargin + movieVMargin) / (movieHeight + movieVMargin);
    fieldVMargin = (QApplication::desktop()->geometry().height() - _rows * (movieHeight + movieVMargin) - movieVMargin) / 2;

    _scrolledBy = 0;
}

void MovieList::populateList(QString directory)
{
    _movieFactoryThread = new MovieFactoryThread(directory);
    connect(&_movieFactoryThread->_movieFactory, SIGNAL(movieCreated(Movie *)), this, SLOT(addMovie(Movie *)), Qt::QueuedConnection);
    _movieFactoryThread->start();
}

void MovieList::addMovie(Movie *movie)
{
    movieWidgets.append(new MovieWidget(movie, this));
    update();
}

void MovieList::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (int i = 0; i < movieWidgets.size(); i++)
    {
        movieWidgets.at(i)->hide();
    }

    for (int i = _scrolledBy * _columns; i < movieWidgets.size(); i++)
    {
        int column = i % _columns;
        int row = (i - _scrolledBy * _columns) / _rows;
        if (row >= _rows)
        {
            break;
        }

        movieWidgets.at(i)->setGeometry(QRect(fieldHMargin + column * (movieWidth + movieHMargin),
                                              fieldVMargin + row * (movieHeight + movieVMargin),
                                              movieWidgets.at(i)->size().width(),
                                              movieWidgets.at(i)->size().height()));
        movieWidgets.at(i)->show();
    }
}

void MovieList::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Down:
            _scrollDown();
            break;
        case Qt::Key_Up:
            _scrollUp();
            break;
    }
}

void MovieList::_scrollUp()
{
    if (_scrolledBy <= 0)
    {
        return;
    }

    _scrolledBy--;
    update();
}

void MovieList::_scrollDown()
{
    if (_scrolledBy >= movieWidgets.size() / _rows - 1)
    {
        return;
    }

    _scrolledBy++;
    update();
}
