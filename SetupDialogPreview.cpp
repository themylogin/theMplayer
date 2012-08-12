#include "SetupDialogPreview.h"

#include <QPainter>
#include <QSize>

SetupDialogPreview::SetupDialogPreview(GridLayout* gridLayout, QWidget *parent)
    : QWidget(parent)
{
    this->gridLayout = gridLayout;
}

void SetupDialogPreview::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    painter.fillRect(0, 0, this->width(), this->height(), QColor(0, 0, 0));

    float factorX = (float)this->width() / this->gridLayout->getGridWidth();
    float factorY = (float)this->height() / this->gridLayout->getGridHeight();

    for (int col = 0; col < this->gridLayout->getCols(); col++)
    {
        for (int row = 0; row < this->gridLayout->getRows(); row++)
        {
            painter.drawRect(QRect(this->gridLayout->getX(col) * factorX,
                                   this->gridLayout->getY(row) * factorY,
                                   this->gridLayout->getElementWidth() * factorX,
                                   this->gridLayout->getElementHeight() * factorY));
        }
    }
}
