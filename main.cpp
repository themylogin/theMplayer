#include "main.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDir>
#include <QSettings>
#include <QStringList>
#include <QThreadPool>

#include "MovieCollection.h"
#include "MovieCollectionModel.h"
#include "SetupDialog.h"

#include <QTreeView>

bool applicationIsSetUpProperly()
{
    QSettings settings;

    if (!settings.contains("setupDone"))
    {
        return false;
    }

    if (!QDir(settings.value("directory").toString()).exists())
    {
        return false;
    }

    return true;
}

bool setupModeArgumentPassed()
{
    return QApplication::arguments().contains(QString("-setup"));
}

void executeSetup()
{
    SetupDialog* setupDialog = new SetupDialog;
    setupDialog->show();
}

void executeMovieList()
{
    QSettings settings;

    MovieCollectionModel* movieCollectionModel = new MovieCollectionModel(settings.value("directory").toString());
    //MovieCollection* movieCollection = new MovieCollection(movieCollectionModel, movieCollectionModel->getRootIndex());
    //movieCollection->showFullScreen();
    QTreeView* tw = new QTreeView();
    tw->setModel(movieCollectionModel);
    tw->setRootIndex(movieCollectionModel->getRootIndex());
    tw->setSortingEnabled(true);
    tw->showFullScreen();
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("theMplayer");
    QApplication::setOrganizationName("themylogin");
    QApplication::setOrganizationDomain("themylogin.ru");

    if (!applicationIsSetUpProperly() || setupModeArgumentPassed())
    {
        executeSetup();
    }
    else
    {
        executeMovieList();
    }

    return app.exec();
}
