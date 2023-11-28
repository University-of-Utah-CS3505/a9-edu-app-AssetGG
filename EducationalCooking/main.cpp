#include "playerview.h"
#include <QApplication>
#include "playermodel.h"
#include "startupscreen.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    PlayerModel model; // Instance of PlayerModel

    StartupScreen startupScreen(model);

    startupScreen.show();

    return a.exec();
}

