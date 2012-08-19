#include "Utils.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>

void Utils::getWidestScreenDimensions(int& width, int& height)
{
    width = 0;
    height = 0;
    for (int screen = 0; screen < QApplication::desktop()->screenCount(); screen++)
    {
        if (QApplication::desktop()->screenGeometry(screen).width() > width)
        {
            width = QApplication::desktop()->screenGeometry(screen).width();
            height = QApplication::desktop()->screenGeometry(screen).height();
        }
    }
}

QStringList Utils::wrapText(const QFont& font, const QString& text, int width)
{
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
                    // try to cut by whitespace
                    int j = i - 1;
                    while (j >= 0 && notWrappedTextPart[j] != ' ')
                    {
                        j--;
                    }
                    if (j > 0)
                    {
                        lines.append(notWrappedTextPart.left(j));
                        notWrappedTextPart = notWrappedTextPart.mid(j + 1);
                    }
                    else
                    {
                        lines.append(notWrappedTextPart.left(i - 1));
                        notWrappedTextPart = notWrappedTextPart.mid(i - 1);
                    }
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

    return lines;
}

QImage Utils::drawOutlinedText(QString text, int width, int height)
{
    int fontSize = 32;
    int lineHeight = 42;
    int textHPadding = 20;
    int textVPadding = 20;
    QFont font = QFont("Impact", fontSize, 800, false);
    QStringList lines = Utils::wrapText(font, text, width - 2 * textHPadding);

    QImage image = QImage(QSize(width, height), QImage::Format_ARGB32);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(QColor(0, 0, 0));
    pen.setWidth(3);
    painter.setPen(pen);
    painter.setBrush(QColor(255, 255, 255));
    QFontMetrics metrics(font);
    for (int i = 0; i < lines.length(); i++)
    {
        QRect lineRect = metrics.boundingRect(lines[i]);

        QPainterPath path;
        path.addText((width - lineRect.width()) / 2,
                     (height - textVPadding - lineHeight * (lines.length() - i - 1)),
                     font, lines[i]);
        painter.drawPath(path);
    }
    return image;
}
