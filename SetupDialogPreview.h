#ifndef SETUPDIALOGPREVIEW_H
#define SETUPDIALOGPREVIEW_H

#include <QWidget>

#include "GridLayout.h"

class SetupDialogPreview : public QWidget
{
    public:
        SetupDialogPreview(GridLayout* gridLayout, QWidget *parent = 0);

    protected:
        void paintEvent(QPaintEvent* pe);

    private:
        GridLayout* gridLayout;
};

#endif // SETUPDIALOGPREVIEW_H
