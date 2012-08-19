#ifndef MOVIECOLLECTIONITEM_H
#define MOVIECOLLECTIONITEM_H

#include <QWidget>

class MovieCollectionItem : public QWidget
{
    public:
        MovieCollectionItem(QWidget* parent = 0)
            : QWidget(parent)
        {
        }

        virtual void activate() = 0;
};

#endif // MOVIECOLLECTIONITEM_H
