#ifndef PHYSICS_H
#define PHYSICS_H

#include <QObject>
#include <QTimer>
#include "Box2D/box2d.h"

class Physics : public QObject
{
    Q_OBJECT
    float timeStep;
    QTimer timer;

public:
    class PhysicsObject
    {
    public:
        /// Data relating to the object's kinetic properties
        /// (i.e. position, velocity, etc).
        /// See Box2D docs for more info.
        b2Body *body;
        /// Data relating to the object's surface/material properties
        /// (i.e. shape, friction, restitution, etc).
        /// See Box2D docs for more info.
        b2Fixture *fixture;
        PhysicsObject(b2Body *body, b2Fixture *fixture);
    };

private:
    b2World world;
    std::map<std::string, Physics::PhysicsObject> objects;

    /// Internal method for updating PhysicsObjects
    void update();

public:
    /// Constructs a physics simulator that will update `updateHz` times
    /// a second when .start() is called.
    explicit Physics(float updateHz = 90.0, QObject *parent = nullptr);

    /// Adds a physics object to the system that is static, meaning it
    /// does not move. Requires the user to provide a shape and x, y
    /// positional coordinates. Returns a reference to the object if
    /// further modifications are desired.
    PhysicsObject &registerStaticObject(std::string name, b2Shape *shape, float x, float y);

    /// Adds a physics object to the system that is dynamic, forces will
    /// make it move. Requires the user to provide a shape and x, y
    /// positional coordinates. Returns a reference to the object if
    /// further modifications are desired.
    PhysicsObject &registerDynamicObject(std::string name, b2Shape *shape, float x, float y);

    /// returns a pointer to the PhysicsObject registered under a given name,
    /// or nullptr if no such object has been registered.
    PhysicsObject *get(std::string name);

    /// constructs a rectangular collision shape for use in
    /// `registerStaticObject` or `registerDynamicObject`
    static b2PolygonShape createBoxShape(float width, float height);
    /// constructs a circular collision shape for use in
    /// `registerStaticObject` or `registerDynamicObject`
    static b2CircleShape createCircleShape(float radius);

    /// starts the physics simulation, to be run at time
    /// `updateHz` times per second
    void start();
    /// stops the physics simulation.
    void stop();

signals:
    /// fired each time the physics are updated, passing along
    /// a read-only reference to the HashMap of physics objects
    void onUpdate(const std::map<std::string, Physics::PhysicsObject> &physicsObjects);
};

#endif // PHYSICS_H
