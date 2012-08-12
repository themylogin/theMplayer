#ifndef MOVIECOLLECTION_H
#define MOVIECOLLECTION_H

#include <QList>
#include <QString>
#include <QWidget>

#include "GridLayout.h"
#include "GridLayoutScrollerWithCursor.h"

class MovieCollection : public QWidget
{
    Q_OBJECT

    public:
        explicit MovieCollection(QString directory, QWidget* parent = 0);

    protected:
        void paintEvent(QPaintEvent* event);

    private:
        GridLayout* layout;
        GridLayoutScrollerWithCursor* scroller;

        QList<QWidget*> movies;
};

#endif // MOVIECOLLECTION_H
