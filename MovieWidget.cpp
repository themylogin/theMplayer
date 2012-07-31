#include <QImage>
#include <QPainter>
#include <QPainterPath>

#include "Movie.h"
#include "MovieWidget.h"
#include "Utils.h"

MovieWidget::MovieWidget(Movie *movie, QWidget *parent)
        : QWidget(parent), movie(movie)
{

    int textHPadding = 10;
    int textVPadding = 10;
    int fontSize = 24;
    int lineHeight = 34;
    QFont font = QFont("Impact", fontSize, 800, false);
    QStringList lines = Utils::wrapText(font, movie->getTitle(), movie->getThumbnail()->size().width() - 2 * textHPadding);

    this->movieTitle = QImage(QSize(movie->getThumbnail()->size().width(), lines.length() * lineHeight), QImage::Format_ARGB32);
    QPainter painter(&this->movieTitle);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QColor(0, 0, 0));
    painter.setBrush(QColor(255, 255, 255));
    for (int i = 0; i < lines.length(); i++)
    {
        QPainterPath path;
        path.addText(textHPadding, textVPadding + fontSize + i * lineHeight, font, lines.at(i));
        painter.drawPath(path);
    }
}

void MovieWidget::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawImage(QRect(0,      (height() - movie->getThumbnail()->height()) / 2,
                            width(), movie->getThumbnail()->height()),
                      *(movie->getThumbnail()));
    painter.drawImage(0, 0, this->movieTitle);

    QPen borderPen;
    borderPen.setBrush(QColor(203, 203, 203));
    borderPen.setWidth(2);
    painter.setPen(borderPen);
    painter.drawRect(0, 0, width(), height());

}

void MovieWidget::activate()
{
    movie->play();
}
