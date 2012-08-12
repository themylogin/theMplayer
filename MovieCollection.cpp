#include "MovieCollection.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QSettings>

#include "Movie.h"

MovieCollection::MovieCollection(QString directory, QWidget* parent) :
    QWidget(parent)
{
    QSettings settings;

    int screenWidth = 0;
    int screenHeight = 0;
    for (int screen = 0; screen < QApplication::desktop()->screenCount(); screen++)
    {
        if (QApplication::desktop()->screenGeometry(screen).width() > screenWidth)
        {
            screenWidth = QApplication::desktop()->screenGeometry(screen).width();
            screenHeight = QApplication::desktop()->screenGeometry(screen).height();
        }
    }

    this->layout = new GridLayout(screenWidth, screenHeight,
                                  settings.value("movieHPadding").toInt(), settings.value("movieVPadding").toInt(),
                                  settings.value("movieWidth").toInt(), settings.value("movieHeight").toInt(),
                                  settings.value("movieHMargin").toInt(), settings.value("movieVMargin").toInt());
    this->scroller = new GridLayoutScrollerWithCursor(this->layout, settings.value("scroll").toString().startsWith('H') ? Horizontal : Vertical);

    QPalette pal = this->palette();
    pal.setColor(this->backgroundRole(), QColor(0, 0, 0));
    this->setPalette(pal);

    if (parent == 0)
    {
        this->movies.append(new MovieCollection(directory, this));
        this->movies.append(new Movie(directory, this));
        this->movies.append(new Movie(directory, this));
        this->movies.append(new Movie(directory, this));
        this->movies.append(new Movie(directory, this));
        this->movies.append(new Movie(directory, this));
        this->movies.append(new Movie(directory, this));
        this->movies.append(new Movie(directory, this));
        this->movies.append(new Movie(directory, this));
    }
    else
    {
        this->movies.append(new Movie(directory, this));
        this->movies.append(new Movie(directory, this));
        this->movies.append(new Movie(directory, this));
        this->movies.append(new Movie(directory, this));
        this->movies.append(new Movie(directory, this));
    }
}

void MovieCollection::paintEvent(QPaintEvent* event)
{
    (void) event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen borderPen;
    borderPen.setBrush(QColor(203, 203, 203));
    borderPen.setWidth(2);
    painter.setPen(borderPen);
    painter.drawRect(0, 0, this->width(), this->height());

    float factorX = (float)this->width() / this->layout->getGridWidth();
    float factorY = (float)this->height() / this->layout->getGridHeight();

    for (int col = 0; col < this->layout->getCols(); col++)
    {
        for (int row = 0; row < this->layout->getRows(); row++)
        {
            int i = this->scroller->indexAt(col, row);
            if (i == -1 || i >= this->movies.length())
            {
                continue;
            }

            this->movies[i]->setGeometry(QRect(this->layout->getX(col) * factorX,
                                               this->layout->getY(row) * factorY,
                                               this->layout->getElementWidth() * factorX,
                                               this->layout->getElementHeight() * factorY));
            this->movies[i]->show();
        }
    }
}
