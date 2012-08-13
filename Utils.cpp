#include "Utils.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QFontMetrics>

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
                    int j = i;
                    while (j >= 0 && notWrappedTextPart[j] != ' ')
                    {
                        j--;
                    }
                    if (j > 0)
                    {
                        i = j;
                    }

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

    return lines;
}
