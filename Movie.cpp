#include "Movie.h"

#include <QDebug>
#include <QPainter>
#include <QPen>

Movie::Movie(QString path, QWidget* parent) :
    QWidget(parent)
{
    this->path = path;
}

void Movie::paintEvent(QPaintEvent* event)
{
    (void) event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen borderPen;
    borderPen.setBrush(QColor(203, 203, 203));
    borderPen.setWidth(2);
    painter.setPen(borderPen);
    painter.drawRect(0, 0, this->width(), this->height());

    painter.drawText(0, 20, this->path);
}
