#include <QKeyEvent>
#include <QPainter>
#include <QSocketNotifier>

#include "MovieFactoryThread.h"
#include "MovieWidget.h"
#include "MovieGrid.h"
#include "Movie.h"
#include "ScrollableGrid.cpp"

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

    movieFactoryThread = new MovieFactoryThread(directory, movieWidth, movieHeight);
    connect(movieFactoryThread, SIGNAL(movieCreated(Movie *)), this, SLOT(addMovie(Movie *)));
    movieFactoryThread->start();

    drawingDirection = dd;
    scrollableGrid = new ScrollableGrid<MovieWidget *>(cols, rows, drawingDirection);

    // initLirc();
}

void MovieGrid::initLirc()
{
    int lirc_socket = lirc_init("theMplayer", 1);
    if (lirc_socket == -1)
    {
        return;
    }

    if (lirc_readconfig(NULL, &lircConfig, NULL) != 0)
    {
        return;
    }

    lircNotifier = new QSocketNotifier(lirc_socket, QSocketNotifier::Read, this);
    connect(lircNotifier, SIGNAL(activated(int)), this, SLOT(lircEvent(int)));
}

void MovieGrid::lircEvent(int socket)
{
    // http://www.lirc.org/html/technical.html
    /*lirc_nextcode(&code)==0)
                {
                        if(code==NULL) continue;
                        while((ret=lirc_code2char(config,code,&c))==0 &&
                              c!=NULL)
                        {
#ifdef DEBUG
                                printf("Execing command \"%s\"\n",c);
#endif
                                system(c);
                        }
                        free(code);
                        if(ret==-1) break;
                }*/
}

void MovieGrid::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);

    for (int i = 0; i < scrollableGrid->list.size(); i++)
    {
        scrollableGrid->list.at(i)->hide();
    }

    drawAll(drawingDirection);
}

void MovieGrid::draw(int col, int row, int x, int y)
{
    QPainter painter(this);

    MovieWidget *w = scrollableGrid->itemAt(col, row);

    if (w != NULL)
    {
        w->setGeometry(QRect(x, y, w->size().width(), w->size().height()));
        w->show();
    }
}

void MovieGrid::keyPressEvent(QKeyEvent *ke)
{
    switch (ke->key())
    {
        case Qt::Key_Down:
        case Qt::Key_Right:
            scrollForward();
            break;
        case Qt::Key_Up:
        case Qt::Key_Left:
            scrollBackward();
            break;
    }
}

void MovieGrid::addMovie(Movie *movie)
{
    MovieWidget *movieWidget = new MovieWidget(movie, this);
    movieWidget->resize(movieWidth, movieHeight);
    scrollableGrid->addItem(movieWidget);
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
