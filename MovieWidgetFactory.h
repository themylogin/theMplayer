#ifndef MOVIEWIDGETFACTORY_H
#define MOVIEWIDGETFACTORY_H

#include "Movie.h"

class QDir;
#include <QObject>
class QString;

class MovieWidgetFactory : public QObject
{
    Q_OBJECT
    enum MovieWidgetFactoryException
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

#endif // MOVIEWIDGETFACTORY_H
