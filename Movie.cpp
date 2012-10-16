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
}

void Movie::paintEvent(QPaintEvent* event)
{
    (void) event;

    if (!this->cachedRepresentations.contains(this->width()))
    {
        QPixmap representation(this->size());

        QPainter painter(&representation);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);

        QImage image = this->image.scaledToWidth(this->width(), Qt::SmoothTransformation);
        painter.drawImage(QRect(0,             (this->height() - image.height()) / 2,
                                image.width(), image.height()),
                          image);

        painter.drawImage(0, 0, Utils::drawOutlinedText(this->title, this->supposedWidth, this->supposedHeight));

        QPen borderPen;
        borderPen.setBrush(QColor(203, 203, 203));
        borderPen.setWidth(2);

        painter.setPen(borderPen);
        painter.setBrush(QColor(0, 0, 0, 0));
        painter.drawRect(0, 0, this->width(), this->height());

        this->cachedRepresentations[this->width()] = representation;
    }

    QPainter painter(this);
    QPixmap pixmap = this->cachedRepresentations[this->width()];
    painter.drawPixmap(0, 0, pixmap.width(), pixmap.height(), pixmap);
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
        this->update();
    }
}
