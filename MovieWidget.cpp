#include <QImage>
#include <QPainter>
#include <QPainterPath>

#include "Movie.h"
#include "MovieWidget.h"

MovieWidget::MovieWidget(Movie *movie, QWidget *parent)
        : QWidget(parent), movie(movie)
{
    setWindowTitle(movie->getTitle());
}

void MovieWidget::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawImage(QRect(0,      (height() - movie->getThumbnail()->height()) / 2,
                            width(), movie->getThumbnail()->height()),
                      *(movie->getThumbnail()));

    QPen borderPen;
    borderPen.setBrush(QColor(203, 203, 203));
    borderPen.setWidth(2);
    painter.setPen(borderPen);
    painter.drawRect(0, 0, width(), height());

    QFont font = QFont("Impact", 24, 800, false);
    QString text = windowTitle();

    int width = 380;
    QStringList lines;
    QFontMetrics metrics(font);
    QString notWrappedTextPart = text;
    while (notWrappedTextPart != "")
    {
        bool wrapped = false;
        for (int i = 1; i < notWrappedTextPart.length(); i++)
        {
            if (metrics.boundingRect(notWrappedTextPart.left(i)).width() > width)
            {
                if (i > 1)
                {
                    lines.append(notWrappedTextPart.left(i - 1));
                    notWrappedTextPart = notWrappedTextPart.mid(i - 1);
                }
                else
                {
                    notWrappedTextPart = notWrappedTextPart.mid(i);
                }
                wrapped = true;
                break;
            }
        }
        if (!wrapped)
        {
            lines.append(notWrappedTextPart);
            break;
        }
    }


    for (int i = 0; i < lines.length(); i++)
    {
        QPainterPath path;
        path.addText(10, 34 + i * 44, font, lines.at(i));
        painter.setPen(QColor(0, 0, 0));
        painter.setBrush(QColor(255, 255, 255));
        painter.drawPath(path);
    }
}


void MovieWidget::mousePressEvent(QMouseEvent *event)
{
    movie->play();
}
