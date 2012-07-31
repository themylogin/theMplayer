#ifndef MOVIEGRID_H
#define MOVIEGRID_H

#include <QList>
class QSocketNotifier;
class QString;
#include <QWidget>

#include "AbstractMovieGrid.h"
#include "DrawingDirection.h"
#include <lirc/lirc_client.h>
class MovieFactoryThread;
class MovieWidget;
class Movie;
#include "ScrollableGrid.h"
#include "ScrollingDirection.h"

class MovieGrid : public QWidget, public AbstractMovieGrid
{
    Q_OBJECT
    public:
        MovieGrid(int _width,                      int _height,
                  int _movieWidth,                 int _movieHeight,
                  int _movieFieldHorizontalMargin, int _movieFieldHorizontalPadding,
                  int _movieFieldVerticalMargin,   int _movieFieldVerticalPadding,
                  QString directory,
                  DrawingDirection dd,
                  QWidget *parent = 0);

    protected:
        QString directory;
        MovieFactoryThread *movieFactoryThread;

        ScrollableGrid<MovieWidget *> *scrollableGrid;
        DrawingDirection drawingDirection;

        void initLirc();
        struct lirc_config *lircConfig;
        QSocketNotifier *lircNotifier;

        void paintEvent(QPaintEvent *pe);
        void draw(int col, int row, int x, int y);

        void keyPressEvent(QKeyEvent *ke);

    public slots:
        void addMovie(Movie *movie);
        void lircEvent(int socket);
        
        void scrollForward();
        void scrollBackward();
};

#endif // MOVIEGRID_H
