/*
 * Name: Everyone
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: This class starts our program and creates the main objects of our game.
 */

#include <QApplication>
#include "controller.h"
#include "physics.h"
#include "playermodel.h"
#include "playerview.h"
#include "startupscreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PlayerView playerView;
    Physics physics;
    PlayerModel model(physics); // Instance of PlayerModel

    Controller c(model, playerView);

    StartupScreen startupScreen(model, playerView);

    startupScreen.show();

    return a.exec();
}
