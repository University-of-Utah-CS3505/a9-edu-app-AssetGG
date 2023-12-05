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

    float objInitialDrag;
    QPoint mousePos;

    void setupGrabConnections();
    void updateGrabForces();
    Tool *getToolAtPoint(QPoint point);

public:
    explicit Controller(PlayerModel &model, PlayerView &view, QObject *parent = nullptr);

public slots:
    void onItemGrabbed(std::string itemName, bool isIngredient, QPoint mousePos);
    void onMouseMoved(QPoint mousePos);
    void onItemDropped(QPoint mousePos);
};

#endif // CONTROLLER_H
