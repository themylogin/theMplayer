#include "Movie.h"

#include <QCryptographicHash>
#include <QDir>
#include <QFont>
#include <QPainter>
#include <QPen>
#include <QProcess>
#include <QSettings>
#include <QStringList>

#include "MovieFile.h"
#include "Utils.h"

Movie::Movie(QString title, QString path, QWidget* parent) :
    MovieCollectionItem(parent)
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
    this->text = Utils::drawOutlinedText(title, this->supposedWidth, this->supposedHeight);
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
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRect(0, 0, this->width(), this->height());

    if (!this->scaledImages.contains(this->width()))
    {
        this->scaledImages[this->width()] = this->image.scaledToWidth(this->width(), Qt::SmoothTransformation);
    }
    QImage image = this->scaledImages[this->width()];
    if (!this->scaledTexts.contains(this->width()))
    {
        this->scaledTexts[this->width()] = this->text.scaledToWidth(this->width(), Qt::SmoothTransformation);
    }
    QImage text = this->scaledTexts[this->width()];
    painter.drawImage(QRect(0,             (this->height() - image.height()) / 2,
                            image.width(), image.height()),
                      image);
    painter.drawImage(0, 0, text);

    painter.setPen(borderPen);
    painter.setBrush(QColor(0, 0, 0, 0));
    painter.drawRect(0, 0, this->width(), this->height());
}

void Movie::activate()
{
    this->process.setEnvironment(QProcess::systemEnvironment());
    this->process.start("./theMplayerShell.py", QStringList() << this->path);
}
