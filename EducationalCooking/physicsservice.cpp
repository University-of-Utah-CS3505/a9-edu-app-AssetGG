#include "physicsservice.h"
#include "Box2D/box2d.h"

using PhysicsObject = PhysicsService::PhysicsObject;

PhysicsService::PhysicsService(QObject *parent)
    : QObject{parent}
    , world(b2World(b2Vec2(0.0, 0.0)))
{}

PhysicsService::PhysicsObject::PhysicsObject(b2Body *body, b2Fixture *fixture)
    : body(body)
    , fixture(fixture)
{}

PhysicsObject &PhysicsService::registerStaticObject(std::string name,
                                                    b2Shape *shape,
                                                    float x,
                                                    float y)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(x, y);
    b2Body *body = world.CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    b2Fixture *fixture = body->CreateFixture(&fixtureDef);

    PhysicsObject object(body, fixture);
    objects.insert({name, object});
    return objects.at(name);
}

PhysicsObject &PhysicsService::registerDynamicObject(std::string name,
                                                     b2Shape *shape,
                                                     float x,
                                                     float y)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    b2Body *body = world.CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 1.0;
    fixtureDef.friction = 0.3;

    b2Fixture *fixture = body->CreateFixture(&fixtureDef);

    PhysicsObject object(body, fixture);
    objects.insert({name, object});
    return objects.at(name);
}

b2PolygonShape PhysicsService::createBoxShape(float width, float height)
{
    b2PolygonShape shape;
    // their implementation takes in half-width and half-heights.
    // For clarity, I'm undoing that decision.
    shape.SetAsBox(width / 2.0, height / 2.0);

    return shape;
}

b2CircleShape PhysicsService::createCircleShape(float radius)
{
    b2CircleShape shape;
    shape.m_p.Set(0.0, 0.0);
    shape.m_radius = radius;
    return shape;
}
