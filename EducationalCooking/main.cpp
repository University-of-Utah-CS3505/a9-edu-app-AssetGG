#include <QApplication>
#include "controller.h"
#include "physics.h"
#include "playermodel.h"
#include "playerview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerModel m;
    PlayerView v;
    Physics physics;
    Controller c(m, v);

    v.show();
    physics.start();
    return a.exec();
}
