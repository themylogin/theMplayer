#ifndef MOVIECOLLECTION_H
#define MOVIECOLLECTION_H

#include <QKeyEvent>
#include <QMap>
#include <QString>
#include <QWidget>

#include "GridLayout.h"
#include "GridLayoutScrollerWithCursor.h"
#include "MovieCollectionItem.h"
#include "MovieCollectionModel.h"

class MovieCollection : public MovieCollectionItem
{
    Q_OBJECT

    public:
        explicit MovieCollection(MovieCollectionModel* model, const QPersistentModelIndex& modelRootIndex, QWidget* parent = 0);

    protected:
        void paintEvent(QPaintEvent* event);
        void keyPressEvent(QKeyEvent* event);

        void activate();

    private:
        int screenWidth;
        int screenHeight;

        GridLayout* layout;
        GridLayoutScrollerWithCursor* scroller;

        MovieCollectionModel* model;
        QPersistentModelIndex modelRootIndex;

        QImage text;
        QMap<int, QImage> scaledTexts;

        QMap<QString, MovieCollectionItem*> movies;
        MovieCollectionItem* produceMovie(const QModelIndex& index);

        QWidget* back;

        QString movieTitle(QString fileName);

    private slots:
        void moviesInserted(const QModelIndex&, int, int);
};

#endif // MOVIECOLLECTION_H
