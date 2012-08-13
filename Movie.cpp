#include "Movie.h"

#include <QFont>
#include <QPainter>
#include <QPen>
#include <QSettings>

#include "Utils.h"

Movie::Movie(QString title, QString path, QWidget* parent) :
    QWidget(parent)
{
    this->title = title;
    this->path = path;

    QSettings settings;
    int width = settings.value("movieWidth").toInt();
    int fontSize = 32;
    int lineHeight = 42;
    int textHPadding = 10;
    int textVPadding = 10;
    QFont font = QFont("Impact", fontSize, 800, false);
    QStringList lines = Utils::wrapText(font, title, width - 2 * textHPadding);

    this->text = QImage(QSize(width, lines.length() * lineHeight + 2 * textVPadding), QImage::Format_ARGB32);
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

void Movie::paintEvent(QPaintEvent* event)
{
    (void) event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QPen borderPen;
    borderPen.setBrush(QColor(203, 203, 203));
    borderPen.setWidth(2);
    painter.setPen(borderPen);
    painter.drawRect(0, 0, this->width(), this->height());

    float factor = (float) this->width() / this->text.width();
    painter.scale(factor, factor);
    painter.drawImage(0, 0, this->text);
}
