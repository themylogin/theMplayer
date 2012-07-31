#include <QPainter>
#include <QPainterPath>

#include "MovieWidget.h"
#include "Utils.h"

MovieWidget::MovieWidget(int width, int height, QString title, QWidget *parent)
        : QWidget(parent)
{
    resize(width, height);

    int fontSize = 32;
    int lineHeight = 42;
    int textHPadding = 10;
    int textVPadding = 10;
    QFont font = QFont("Impact", fontSize, 800, false);
    QStringList lines = Utils::wrapText(font, title, this->width() - 2 * textHPadding);

    this->text = QImage(QSize(this->width(), lines.length() * lineHeight + 2 * textVPadding), QImage::Format_ARGB32);
    QPainter painter(&this->text);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(QColor(0, 0, 0));
    pen.setWidth(3);
    painter.setPen(pen);
    painter.setBrush(QColor(255, 255, 255));
    for (int i = 0; i < lines.length(); i++)
    {
        QPainterPath path;
        path.addText(textHPadding, textVPadding + fontSize + i * lineHeight, font, lines.at(i));
        painter.drawPath(path);
    }
}

void MovieWidget::paintBorder()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen borderPen;
    borderPen.setBrush(QColor(203, 203, 203));
    borderPen.setWidth(2);
    painter.setPen(borderPen);
    painter.drawRect(0, 0, this->width(), this->height());
}

void MovieWidget::paintText()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawImage(0, 0, this->text);
}
