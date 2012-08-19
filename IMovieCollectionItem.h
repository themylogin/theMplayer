#ifndef IMOVIECOLLECTIONITEM_H
#define IMOVIECOLLECTIONITEM_H

#include <QWidget>

class IMovieCollectionItem : public QWidget
{
    public:
        IMovieCollectionItem(QWidget* parent = 0)
            : QWidget(parent)
        {
        }

        virtual void activate() = 0;
};

#endif // IMOVIECOLLECTIONITEM_H
