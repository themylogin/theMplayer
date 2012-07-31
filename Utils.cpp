#include "Utils.h"

#include <QFontMetrics>

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
