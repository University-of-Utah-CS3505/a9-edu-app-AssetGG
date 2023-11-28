#include <QApplication>
#include "controller.h"
#include "playermodel.h"
#include "playerview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerModel m;
    PlayerView v;
    Controller c(m, v);
    v.show();
    return a.exec();
}
