#include "main.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDir>
#include <QSettings>
#include <QStringList>

#include "MovieCollection.h"
#include "MovieCollectionModel.h"
#include "SetupDialog.h"

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

    MovieCollectionModel* mcm = new MovieCollectionModel(settings.value("directory").toString());
    QPersistentModelIndex mcmi = mcm->getRootIndex();
    MovieCollection* mc = new MovieCollection(mcm, mcmi);
    mc->showFullScreen();
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
