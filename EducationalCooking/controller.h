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
    QPoint mousePos;

    void setupGrabConnections();
    void updateGrabForces();

public:
    explicit Controller(PlayerModel &model, PlayerView &view, QObject *parent = nullptr);

public slots:
    void onIngredientGrabbed(std::string ingredientName, QPoint mousePos);
    void onMouseMoved(QPoint mousePos);
    void onIngredientDropped(QPoint mousePos);
};

#endif // CONTROLLER_H
