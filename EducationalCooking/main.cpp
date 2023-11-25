#include "playerview.h"
#include <QApplication>
#include "playermodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerModel m;
    PlayerView w(m);
    w.show();
    return a.exec();
}
