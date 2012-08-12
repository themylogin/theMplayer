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

    QStringList keysToShow;
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
}

QWidget* MovieCollection::produceMovie(const QModelIndex& index)
{
    if (this->model->isDir(index))
    {
        return new MovieCollection(this->model, QPersistentModelIndex(index), this);
    }
    else
    {
        return new Movie(this->model->fileName(index), this);
    }
}
