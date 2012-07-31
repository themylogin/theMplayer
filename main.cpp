#include <QApplication>
#include <QDesktopWidget>
#include <QDir>
#include <QSettings>
#include <QStringList>

#include "DrawingDirection.h"
#include "main.h"
#include "MovieGrid.h"
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
    SetupDialog *setupDialog = new SetupDialog;
    setupDialog->show();
}

void executeMovieList()
{
    QSettings settings;

    MovieGrid *movieGrid = new
              MovieGrid(1920, 1080,
                        settings.value("movieWidth").toInt(), settings.value("movieHeight").toInt(),
                        settings.value("movieFieldHMargin").toInt(), settings.value("movieFieldHPadding").toInt(),
                        settings.value("movieFieldVMargin").toInt(), settings.value("movieFieldVPadding").toInt(),
                        settings.value("directory").toString(),
                        settings.value("scroll").toString().startsWith('H') ? Horizontal : Vertical);
    movieGrid->showFullScreen();
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
    } else {
        executeMovieList();
    }

    return app.exec();
}
