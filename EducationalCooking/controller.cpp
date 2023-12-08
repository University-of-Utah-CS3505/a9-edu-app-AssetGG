#include "controller.h"
#include "physics.h"
#include "playermodel.h"
#include "playerview.h"
#include "finalscreen.h"

#include <QTimer>

Controller::Controller(PlayerModel &model, PlayerView &view, QObject *parent)
    : view(view)
    , model(model)
    , grabbedPhysicsObject(nullptr)
    , canGrab(true)
    , objInitialDrag(0.0)
{
    connect(&model.physics, &Physics::onUpdate, &view, &PlayerView::updateSpritePositions);
    connect(&model.physics, &Physics::onUpdate, this, &Controller::updateGrabForces);
    connect(&view, &PlayerView::calculateScoreRequested, &model, &PlayerModel::calculateScore);
    connect(&view, &PlayerView::getFinalIngredientsRequested, &model, &PlayerModel::getFinalIngredients);
    connect(&view, &PlayerView::addItemToFinalDishIngredients, &model, &PlayerModel::addIngredientToFinalDish);

    setupGrabConnections();
}

void Controller::onItemGrabbed(std::string itemName, bool isIngredient, QPoint mousePos)
{
    if (canGrab) {
        this->mousePos = mousePos;
        grabbedPhysicsObject = model.physics.get(itemName);
        grabbedObjectName = itemName;
        grabbedObjectIsIngredient = isIngredient;
        objInitialDrag = grabbedPhysicsObject->body->GetLinearDamping();

        grabbedPhysicsObject->body->SetLinearDamping(objInitialDrag * 2.0);
    }
}

void Controller::onMouseMoved(QPoint mousePos)
{
    this->mousePos = mousePos;
}

void Controller::onItemDropped(QPoint mousePos)
{
    this->mousePos = mousePos;
    if (grabbedPhysicsObject) {
        if (grabbedObjectIsIngredient) {
            Tool *toolUnderMouse = getToolAtPoint(mousePos);
            if (toolUnderMouse) {
                // messy, but too late to go back on this bad design decision. Sorry :(
                Ingredient *ingredient = view.getIngredientByName(grabbedObjectName);
                toolUnderMouse->ProcessIngredient(*ingredient);
            }
        }

        // let the object "fly" for a bit before it slows down.
        b2Body *tempRef = grabbedPhysicsObject->body;
        tempRef->SetLinearDamping(objInitialDrag / 7.0);

        // free up this variable in case the user wants to grab something else in the next quarter second
        grabbedPhysicsObject = nullptr;
        canGrab = false;

        // after a quarter second, increase the damping to make it skid to a stop.
        QTimer::singleShot(250, this, [this, tempRef] {
            this->canGrab = true;
            tempRef->SetLinearDamping(tempRef->GetLinearDamping() * 7.0);
        });
    }
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

Tool *Controller::getToolAtPoint(QPoint point)
{
    for (auto &[toolName, tool] : model.getTools()) {
        PhysicsObject *physObj = model.physics.get(toolName);
        if (physObj) {
            b2Transform transform = physObj->body->GetTransform();
            bool pointInShape = physObj->fixture->GetShape()->TestPoint(transform,
                                                                        b2Vec2(point.x(),
                                                                               point.y()));
            if (pointInShape) {
                return tool;
            }
        }
    }

    return nullptr;
}
