#ifndef UTILS_H
#define UTILS_H

#include <QFont>
#include <QImage>
#include <QMutex>
#include <QStringList>

class Utils
{
    public:
        static void getWidestScreenDimensions(int& width, int& height);
        static QStringList wrapText(const QFont& font, const QString& text, int width);
        static QImage drawOutlinedText(QString text, int width, int height);
        static QImage getMovieThumbnail(QString filename);
        static QImage loadImageFromFile(QString filename);

   private:
        static bool     avRegistered;
        static QMutex   avRegisteredMutex;
        static QMutex   avCodecMutex;
};

#endif // UTILS_H
