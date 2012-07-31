#ifndef MOVIEWIDGET_H
#define MOVIEWIDGET_H

#include <QImage>
#include <QString>
#include <QWidget>

class MovieWidget : public QWidget
{
    Q_OBJECT

    public:
        MovieWidget(int width, int height, QString title, QWidget *parent = 0);
        virtual void activate() = 0;

    protected:
        QImage text;

        void paintBorder();
        void paintText();
};

#endif // MOVIEWIDGET_H
