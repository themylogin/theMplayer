#include "Movie.h"

#include <QCryptographicHash>
#include <QDir>
#include <QFont>
#include <QPainter>
#include <QPen>
#include <QSettings>

#include "MovieFile.h"
#include "Utils.h"

Movie::Movie(QString title, QString path, QWidget* parent) :
    QWidget(parent)
{
    this->title = title;
    this->path = path;

    QSettings settings;
    this->supposedWidth = settings.value("movieWidth").toInt();
    this->supposedHeight = settings.value("movieHeight").toInt();

    // image
    QString thumbnailsDir = QDir::homePath() + "/.thumbnails";
    if (!QDir(thumbnailsDir).exists())
    {
        QDir(thumbnailsDir).mkdir(thumbnailsDir);
    }

    QString theMplayerThumbnailsDir = thumbnailsDir + "/theMplayer";
    if (!QDir(theMplayerThumbnailsDir).exists())
    {
        QDir(theMplayerThumbnailsDir).mkdir(theMplayerThumbnailsDir);
    }

    QString cacheFilename = theMplayerThumbnailsDir + "/" + QString(QCryptographicHash::hash(
        (path + "#" + QString::number(this->supposedWidth) + "#" + QString::number(this->supposedHeight)).toUtf8(),
        QCryptographicHash::Md5).toHex()) + ".jpg";
    if (QFile::exists(cacheFilename))
    {
        this->image = QImage(cacheFilename);
    }
    else
    {
        MovieFile* movieFile = new MovieFile(path);
        int thumbnailWidth = this->supposedWidth;
        int thumbnailHeight = -1;
        uint8_t* thumbnailData = movieFile->getRGB32Thumbnail(thumbnailWidth, thumbnailHeight);
        this->image = QImage(thumbnailData, thumbnailWidth, thumbnailHeight, QImage::Format_ARGB32);
        // delete movieFile;
        this->image.save(cacheFilename, 0, 85);
    }

    // text
    int fontSize = 32;
    int lineHeight = 42;
    int textHPadding = 20;
    int textVPadding = 20;
    QFont font = QFont("Impact", fontSize, 800, false);
    QStringList lines = Utils::wrapText(font, title, this->supposedWidth - 2 * textHPadding);

    this->text = QImage(QSize(this->supposedWidth, this->supposedHeight), QImage::Format_ARGB32);
    QPainter painter(&this->text);
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
        path.addText((this->supposedWidth - lineRect.width()) / 2,
                     (this->supposedHeight - textVPadding - lineHeight * (lines.length() - i - 1)),
                     font, lines[i]);
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

    painter.save();
    painter.scale((float) this->width() / this->supposedWidth, (float) this->height() / this->supposedHeight);
    {
        painter.drawImage(QRect(0,                   (this->supposedHeight - this->image.height()) / 2,
                                this->image.width(), this->image.height()),
                          this->image);
        painter.drawImage(0, 0, this->text);
    }
    painter.restore();

    QPen borderPen;
    borderPen.setBrush(QColor(203, 203, 203));
    borderPen.setWidth(2);
    painter.setPen(borderPen);
    painter.drawRect(0, 0, this->width(), this->height());
}
