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
    Controller c(m, v);

    Physics physics(15.0);

    auto box = Physics::createBoxShape(1.0, 1.0);
    physics.registerStaticObject("wall", &box, 0.0, 50.0);

    auto circle = Physics::createCircleShape(1.0);
    auto tomato = physics.registerDynamicObject("tomato", &circle, 0.0, 0.0);

    tomato.body->SetLinearVelocity(b2Vec2(0.0, 12.0));

    v.show();
    physics.start();

    return a.exec();
}
