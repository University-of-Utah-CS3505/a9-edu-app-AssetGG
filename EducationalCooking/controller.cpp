#include "controller.h"
#include "physics.h"
#include "playermodel.h"
#include "playerview.h"

#include <QTimer>

Controller::Controller(PlayerModel &model, PlayerView &view, QObject *parent)
    : view(view)
    , model(model)
    , grabbedPhysicsObject(nullptr)
{
    connect(&model.physics, &Physics::onUpdate, &view, &PlayerView::updateSpritePositions);
    connect(&model.physics, &Physics::onUpdate, this, &Controller::updateGrabForces);
    setupGrabConnections();
}

void Controller::setupGrabConnections()
{
    connect(&view, &PlayerView::ingredientGrabbed, this, &Controller::onIngredientGrabbed);
    connect(&view, &PlayerView::ingredientDropped, this, &Controller::onIngredientDropped);
    connect(&view, &PlayerView::updateIngredientPosition, this, &Controller::onMouseMoved);
}

void Controller::updateGrabForces()
{
    if (grabbedPhysicsObject) {
        b2Body *body = grabbedPhysicsObject->body;

        b2Vec2 delta = b2Vec2(mousePos.x() - body->GetPosition().x,
                              mousePos.y() - body->GetPosition().y);

        //delta = b2Vec2(delta.x * abs(delta.x), delta.y * abs(delta.y));
        b2Vec2 force = 120.0 * body->GetMass() * delta;
        //body->SetLinearVelocity(0.9 * body->GetLinearVelocity());
        grabbedPhysicsObject->body->ApplyForceToCenter(force, true);
    }
}

void Controller::onIngredientGrabbed(std::string ingredientName, QPoint mousePos)
{
    this->mousePos = mousePos;
    grabbedPhysicsObject = model.physics.get(ingredientName);
    grabbedPhysicsObject->body->SetLinearDamping(10.0);
}

void Controller::onMouseMoved(QPoint mousePos)
{
    this->mousePos = mousePos;
}

void Controller::onIngredientDropped(QPoint mousePos)
{
    this->mousePos = mousePos;
    if (grabbedPhysicsObject) {
        grabbedPhysicsObject->body->SetLinearDamping(1.0);

        PhysicsObject *tempRef = grabbedPhysicsObject;
        grabbedPhysicsObject = nullptr;
        // let the object "fly" for a bit before it slows down.
        QTimer::singleShot(250, this, [tempRef] { tempRef->body->SetLinearDamping(5.0); });
    }
}
