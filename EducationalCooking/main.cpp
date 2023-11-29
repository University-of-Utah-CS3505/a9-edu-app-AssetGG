#include <QApplication>
#include "controller.h"
#include "physicsservice.h"
#include "playermodel.h"
#include "playerview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerModel m;
    PlayerView v;
    Controller c(m, v);

    PhysicsService physics;

    b2PolygonShape box = PhysicsService::createBoxShape(1.0, 1.0);
    physics.registerStaticObject("wall", &box, 0.0, 50.0);

    auto circle = PhysicsService::createCircleShape(1.0);
    auto tomato = physics.registerDynamicObject("tomato", &circle, 0.0, 0.0);

    //tomato.body->SetLinearVelocity(b2Vec2(0.0, 1.0));

    v.show();
    return a.exec();
}
