#include <QString>

#include "Movie.h"
#include "MovieWidgetFactory.h"
#include "MovieWidgetFactoryThread.h"

MovieWidgetFactoryThread::MovieWidgetFactoryThread(QString directory, int thumbnailWidth, int thumbnailHeight)
        : directory(directory), thumbnailWidth(thumbnailWidth), thumbnailHeight(thumbnailHeight)
{
    factory = new MovieWidgetFactory;
    connect(factory, SIGNAL(movieCreated(Movie *)), this, SLOT(acceptMovie(Movie *)));
}

MovieWidgetFactoryThread::~MovieWidgetFactoryThread()
{
    delete factory;
}

void MovieWidgetFactoryThread::run()
{
    factory->createMovies(directory, thumbnailWidth, thumbnailHeight);
}

void MovieWidgetFactoryThread::acceptMovie(Movie *movie)
{
    emit movieCreated(movie);
}
