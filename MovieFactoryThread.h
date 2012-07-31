#ifndef MOVIEFACTORYTHREAD_H
#define MOVIEFACTORYTHREAD_H

class Movie;
class MovieFactory;
class QString;
#include <QThread>

class MovieFactoryThread : public QThread
{
    Q_OBJECT
    public:
        MovieFactoryThread(QString directory, int thumbnailWidth, int thumbnailHeighte);
        ~MovieFactoryThread();
        void run();

    private:        
        QString directory;
        int thumbnailWidth, thumbnailHeight;
        MovieFactory *factory;

    public slots:
        void acceptMovie(Movie *movie);

    signals:
        void movieCreated(Movie *);
};

#endif // MOVIEFACTORYTHREAD_H
