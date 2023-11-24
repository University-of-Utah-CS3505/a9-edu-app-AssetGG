#include "playerview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerView w;
    w.show();
    return a.exec();
}
