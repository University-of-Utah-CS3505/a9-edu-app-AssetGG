#include <QApplication>
#include "controller.h"
#include "physics.h"
#include "playermodel.h"
#include "startupscreen.h"
#include "playerview.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    PlayerModel model; // Instance of PlayerModel

    PlayerView playerView;
    Physics physics;
    Controller c(model, playerView);

    physics.start();
  
    StartupScreen startupScreen(model);

    startupScreen.show();
  
    return a.exec();
}

