#ifndef MOVIE_H
#define MOVIE_H

#include <QString>
#include <QWidget>

class Movie : public QWidget
{
    Q_OBJECT

    public:
        explicit Movie(QString path, QWidget* parent = 0);

    protected:
        void paintEvent(QPaintEvent* event);

    private:
        QString path;
};

#endif // MOVIE_H
