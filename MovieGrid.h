#ifndef MOVIEGRID_H
#define MOVIEGRID_H

#include <QList>
class QString;
#include <QWidget>

#include "AbstractMovieGrid.h"
#include "DrawingDirection.h"
class MovieWidgetFactory;
class MovieWidget;
class Movie;
#include "ScrollableGridWithCursor.h"
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
        MovieWidgetFactory* movieWidgetFactory;
        QList<MovieWidget*> movieWidgets;

        ScrollableGridWithCursor* scrollableGrid;
        DrawingDirection drawingDirection;

        void paintEvent(QPaintEvent *pe);
        void draw(int col, int row, int x, int y);

        void keyPressEvent(QKeyEvent *ke);

        void addMovieWidget(MovieWidget* movieWidget);

    public slots:
        void addMovieWidget_Movie(Movie*);
        void addMovieWidget_Directory(QString, QString);
        
        void scrollForward();
        void scrollBackward();
};

#endif // MOVIEGRID_H
