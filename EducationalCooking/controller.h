/*
 * Name: David Cosby
 * Reviewed By: Kazimar Guenther
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: Serves as a glue between view and model interactions.
 * Primarily handles questions of how user input on the view should
 * update data stored in the model.
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "physics.h"
#include "playermodel.h"
#include "playerview.h"

using PhysicsObject = Physics::PhysicsObject;

class Controller : public QObject
{
    Q_OBJECT
    PlayerView &view;
    PlayerModel &model;

    PhysicsObject *grabbedPhysicsObject;
    std::string grabbedObjectName;
    bool grabbedObjectIsIngredient;
    bool canGrab;

    float objInitialDrag;
    QPoint mousePos;

public:
    explicit Controller(PlayerModel &model, PlayerView &view, QObject *parent = nullptr);

public slots:
    /// finds the physics object for the grabbed item and preps it
    /// so the updateGrabForces() method will start moving it around.
    void onItemGrabbed(std::string itemName, bool isIngredient, QPoint mousePos);

    /// Updates the controller's copy of the mousePos, for use by updateGrabForces()
    void onMouseMoved(QPoint mousePos);

    /// Temporarily decreases friction on the grabbed object for some
    /// satisfying "throwing" and then clears up references to the dragged object.
    void onItemDropped(QPoint mousePos);

private:
    /// establishes connections between the view's grab-specific events and the slots on this class
    void setupGrabConnections();

    /// Uses hooke's law equations to move the grabbed object towards the mouse
    void updateGrabForces();

    /// Returns a pointer to the tool under the position provided, if one exists.
    /// Otherwise returns a nullptr. Useful for telling which tool a user is mousing over.
    Tool *getToolAtPoint(QPoint point);
};

#endif // CONTROLLER_H
