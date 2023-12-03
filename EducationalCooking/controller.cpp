#include "controller.h"
#include "physics.h"
#include "playermodel.h"
#include "playerview.h"

#include <QTimer>

Controller::Controller(PlayerModel &model, PlayerView &view, QObject *parent)
    : view(view)
    , model(model)
    , grabbedPhysicsObject(nullptr)
    , objInitialDrag(0.0)
{
    connect(&model.physics, &Physics::onUpdate, &view, &PlayerView::updateSpritePositions);
    connect(&model.physics, &Physics::onUpdate, this, &Controller::updateGrabForces);
    connect(&view, &PlayerView::calculateScoreRequested, &model, &PlayerModel::calculateScore);

    setupGrabConnections();
}

void Controller::setupGrabConnections()
{
    connect(&view, &PlayerView::itemGrabbed, this, &Controller::onItemGrabbed);
    connect(&view, &PlayerView::itemDropped, this, &Controller::onItemDropped);
    connect(&view, &PlayerView::updateDragPosition, this, &Controller::onMouseMoved);
}

void Controller::updateGrabForces()
{
    if (grabbedPhysicsObject) {
        b2Body *body = grabbedPhysicsObject->body;

        b2Vec2 delta = b2Vec2(mousePos.x() - body->GetPosition().x,
                              mousePos.y() - body->GetPosition().y);

        b2Vec2 force = 120.0 * body->GetMass() * delta;
        grabbedPhysicsObject->body->ApplyForceToCenter(force, true);
    }
}

void Controller::onItemGrabbed(std::string ingredientName, QPoint mousePos)
{
    this->mousePos = mousePos;
    grabbedPhysicsObject = model.physics.get(ingredientName);
    objInitialDrag = grabbedPhysicsObject->body->GetLinearDamping();

    grabbedPhysicsObject->body->SetLinearDamping(objInitialDrag * 2.0);
}


void Controller::onMouseMoved(QPoint mousePos)
{
    this->mousePos = mousePos;
}

void Controller::onItemDropped(QPoint mousePos)
{
    this->mousePos = mousePos;
    if (grabbedPhysicsObject) {
        // let the object "fly" for a bit before it slows down.
        b2Body *tempRef = grabbedPhysicsObject->body;
        tempRef->SetLinearDamping(objInitialDrag / 7.0);
        float skidDrag = objInitialDrag;

        // free up this variable in case the user wants to grab something else in the next quarter second
        grabbedPhysicsObject = nullptr;
        // after a quarter second, increase the damping to make it skid to a stop.
        QTimer::singleShot(250, this, [tempRef, skidDrag] { tempRef->SetLinearDamping(skidDrag); });
    }
}
