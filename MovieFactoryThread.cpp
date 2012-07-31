#include <QString>

#include "Movie.h"
#include "MovieFactory.h"
#include "MovieFactoryThread.h"

MovieFactoryThread::MovieFactoryThread(QString directory, int thumbnailWidth, int thumbnailHeight)
        : directory(directory), thumbnailWidth(thumbnailWidth), thumbnailHeight(thumbnailHeight)
{
    factory = new MovieFactory;
    connect(factory, SIGNAL(movieCreated(Movie *)), this, SLOT(acceptMovie(Movie *)));
}

MovieFactoryThread::~MovieFactoryThread()
{
    delete factory;
}

void MovieFactoryThread::run()
{
    factory->createMovies(directory, thumbnailWidth, thumbnailHeight);
}

void MovieFactoryThread::acceptMovie(Movie *movie)
{
    emit movieCreated(movie);
}

