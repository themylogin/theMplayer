#include "MovieCollection.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QSettings>
#include <QStringList>

#include "Movie.h"
#include "Utils.h"

#include <QDebug>

MovieCollection::MovieCollection(MovieCollectionModel* model, const QPersistentModelIndex& modelRootIndex, QWidget* parent) :
    QWidget(parent)
{
    QSettings settings;

    Utils::getWidestScreenDimensions(this->screenWidth, this->screenHeight);

    this->layout = new GridLayout(this->screenWidth, this->screenHeight,
                                  settings.value("movieHPadding").toInt(), settings.value("movieVPadding").toInt(),
                                  settings.value("movieWidth").toInt(), settings.value("movieHeight").toInt(),
                                  settings.value("movieHMargin").toInt(), settings.value("movieVMargin").toInt());
    this->scroller = new GridLayoutScrollerWithCursor(this->layout, settings.value("scroll").toString().startsWith('H') ? Horizontal : Vertical);

    QPalette pal = this->palette();
    pal.setColor(this->backgroundRole(), QColor(0, 0, 0));
    this->setPalette(pal);

    this->model = model;
    this->modelRootIndex = modelRootIndex;
    connect(this->model, SIGNAL(rowsInserted(const QModelIndex&, int, int)), this, SLOT(test(const QModelIndex&, int, int)));
    connect(this->model, SIGNAL(rowsMoved(const QModelIndex &, int, int, const QModelIndex &, int)), this, SLOT(test2(const QModelIndex &, int, int, const QModelIndex &, int)));
}

void MovieCollection::test(const QModelIndex&, int, int)
{
    qDebug() << "rowsInserted";
    update();
}

void MovieCollection::test2(const QModelIndex &, int, int, const QModelIndex &, int)
{
    qDebug() << "rowsMoved";
    update();
}

void MovieCollection::paintEvent(QPaintEvent* event)
{
    (void) event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (this->parent() != 0)
    {
        QPen borderPen;
        borderPen.setBrush(QColor(203, 203, 203));
        borderPen.setWidth(2);
        painter.setPen(borderPen);
        painter.drawRect(0, 0, this->width(), this->height());
    }

    float factorX = (float)this->width() / this->layout->getGridWidth();
    float factorY = (float)this->height() / this->layout->getGridHeight();

    // Elements
    QStringList keysToShow;    
    this->model->invalidate();
    for (int col = 0; col < this->layout->getCols(); col++)
    {
        for (int row = 0; row < this->layout->getRows(); row++)
        {
            int i = this->scroller->indexAt(col, row);
            if (i == -1 || !this->model->hasIndex(i, 0, this->modelRootIndex))
            {
                continue;
            }

            QModelIndex index = this->model->index(i, 0, this->modelRootIndex);
            QString key = this->model->filePath(index);
            if (!this->movies.contains(key))
            {
                this->movies[key] = this->produceMovie(index);
            }

            this->movies[key]->setGeometry(QRect(this->layout->getX(col) * factorX,
                                                 this->layout->getY(row) * factorY,
                                                 this->layout->getElementWidth() * factorX,
                                                 this->layout->getElementHeight() * factorY));
            keysToShow.append(key);
        }
    }
    for (auto i = this->movies.begin(); i != this->movies.end(); ++i)
    {
        if (!keysToShow.contains(i.key()))
        {
            i.value()->hide();
        }
    }
    for (int i = 0; i < keysToShow.length(); i++)
    {
        this->movies[keysToShow[i]]->show();
    }

    // Cursor
    for (int col = 0; col < this->layout->getCols(); col++)
    {
        for (int row = 0; row < this->layout->getRows(); row++)
        {
            if (this->scroller->isCurrent(col, row))
            {
                QPen pen(QColor(255, 0, 0));
                pen.setWidth(this->layout->getElementHMargin() * factorX);

                painter.setPen(pen);
                painter.drawRect(QRect((this->layout->getX(col)) * factorX,
                                       (this->layout->getY(row)) * factorY,
                                       (this->layout->getElementWidth()) * factorX,
                                       (this->layout->getElementHeight()) * factorY));
            }
        }
    }
}

void MovieCollection::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Up:
            this->scroller->up(this->model->rowCount(this->modelRootIndex));
            update();
            break;
        case Qt::Key_Down:
            this->scroller->down(this->model->rowCount(this->modelRootIndex));
            update();
            break;
        case Qt::Key_Left:
            this->scroller->left(this->model->rowCount(this->modelRootIndex));
            update();
            break;
        case Qt::Key_Right:
            this->scroller->right(this->model->rowCount(this->modelRootIndex));
            update();
            break;
    }
}

QWidget* MovieCollection::produceMovie(const QModelIndex& index)
{
    if (this->model->isDir(index))
    {
        return new MovieCollection(this->model, QPersistentModelIndex(index), this);
    }
    else
    {
        return new Movie(this->movieTitle(this->model->fileName(index)), this->model->filePath(index), this);
    }
}

QString MovieCollection::movieTitle(QString fileName)
{
    QString title = fileName.simplified();
    title.replace(QRegExp("\\.[a-zA-Z0-9]*$"), QString("")); // cut extension
    title.replace(QRegExp("\\.|_"), QString(" "));
    return title;
}
