#ifndef TESTMOVIEWIDGET_H
#define TESTMOVIEWIDGET_H

#include <QWidget>

#include "GridLayout.h"

class TestMovieWidget : public QWidget
{
    public:
        TestMovieWidget(GridLayout* gridLayout, QWidget *parent = 0);

    protected:
        void paintEvent(QPaintEvent* pe);

    private:
        GridLayout* gridLayout;
};

#endif // TESTMOVIEWIDGET_H
