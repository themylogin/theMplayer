#include "Movie.h"

#include <QCryptographicHash>
#include <QDir>
#include <QFont>
#include <QMovie>
#include <QPainter>
#include <QPen>
#include <QProcess>
#include <QSettings>
#include <QStringList>
#include <QtConcurrentRun>

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

    this->cacheFilename = theMplayerThumbnailsDir + "/" + QString(QCryptographicHash::hash(
        (path + "#" + QString::number(this->supposedWidth) + "#" + QString::number(this->supposedHeight)).toUtf8(),
        QCryptographicHash::Md5).toHex()) + ".jpg";
    if (QFile::exists(this->cacheFilename))
    {
        this->image = QImage(this->cacheFilename);
    }
    else
    {
        this->image = QImage(":/images/loading.png");

        this->futureImage = QtConcurrent::run(&Utils::getMovieThumbnail, path);
        connect(&this->futureImageWatcher, SIGNAL(finished()), this, SLOT(futureImageReady()));
        this->futureImageWatcher.setFuture(this->futureImage);
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
        this->scaledImages[this->width()] = QPixmap::fromImage(this->image.scaledToWidth(this->width(), Qt::SmoothTransformation));
    }
    QPixmap image = this->scaledImages[this->width()];
    if (!this->scaledTexts.contains(this->width()))
    {
        this->scaledTexts[this->width()] = QPixmap::fromImage(this->text.scaledToWidth(this->width(), Qt::SmoothTransformation));
    }
    QPixmap text = this->scaledTexts[this->width()];
    painter.drawPixmap(QRect(0,             (this->height() - image.height()) / 2,
                            image.width(), image.height()),
                       image);
    painter.drawPixmap(0, 0, text);

    painter.setPen(borderPen);
    painter.setBrush(QColor(0, 0, 0, 0));
    painter.drawRect(0, 0, this->width(), this->height());
}

void Movie::activate()
{
    this->process.setEnvironment(QProcess::systemEnvironment());
    this->process.start("./theMplayerShell.py", QStringList() << this->path);
}

void Movie::futureImageReady()
{
    if (!this->futureImage.result().isNull())
    {
        this->image = this->futureImage.result();
        this->image.save(this->cacheFilename);
        this->scaledImages.clear();
        this->update();
    }
}
