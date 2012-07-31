#ifndef MOVIEFACTORY_H
#define MOVIEFACTORY_H

#include "Movie.h"

class QDir;
#include <QObject>
class QString;

class MovieFactory : public QObject
{
    Q_OBJECT
    enum MovieFactoryException
    {
        NoSuchDirectory
    };

    public:
        void createMovies(QString directoryName, int thumbnailWidth, int thumbnailHeight, bool _firstCall = true);

    private:
        void createDVDMovie(QDir directory);

        QString stripFromTitles;
        QString makeTitle(QString absoluteFilePath);

    signals:
        void movieCreated(Movie *);
};

#endif // MOVIEFACTORY_H
