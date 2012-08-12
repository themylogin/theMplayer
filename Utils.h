#ifndef UTILS_H
#define UTILS_H

#include <QFont>
#include <QStringList>

class Utils
{
    public:
        static void getWidestScreenDimensions(int& width, int& height);
        static QStringList wrapText(const QFont& font, const QString& text, int width);
};

#endif // UTILS_H
