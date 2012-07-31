#ifndef MOVIEWIDGETFACTORYTHREAD_H
#define MOVIEWIDGETFACTORYTHREAD_H

class Movie;
class MovieWidgetFactory;
class QString;
#include <QThread>

class MovieWidgetFactoryThread : public QThread
{
    Q_OBJECT
    public:
        MovieWidgetFactoryThread(QString directory, int thumbnailWidth, int thumbnailHeighte);
        ~MovieWidgetFactoryThread();
        void run();

    private:        
        QString directory;
        int thumbnailWidth, thumbnailHeight;
        MovieWidgetFactory* factory;

    public slots:
        void acceptMovie(Movie *movie);

    signals:
        void movieCreated(Movie *);
};

#endif // MOVIEWIDGETFACTORYTHREAD_H
