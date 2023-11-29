#ifndef PHYSICSSERVICE_H
#define PHYSICSSERVICE_H

#include <QObject>
#include "Box2D/box2d.h"

class PhysicsService : public QObject
{
    Q_OBJECT

public:
    class PhysicsObject
    {
    public:
        b2Body *body;
        b2Fixture *fixture;
        PhysicsObject(b2Body *body, b2Fixture *fixture);
    };

private:
    b2World world;
    std::map<std::string, PhysicsService::PhysicsObject> objects;

public:
    explicit PhysicsService(QObject *parent = nullptr);

    PhysicsObject &registerStaticObject(std::string name, b2Shape *shape, float x, float y);
    PhysicsObject &registerDynamicObject(std::string name, b2Shape *shape, float x, float y);

    static b2PolygonShape createBoxShape(float width, float height);
    static b2CircleShape createCircleShape(float radius);

signals:
};

#endif // PHYSICSSERVICE_H
