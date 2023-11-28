#ifndef PHYSICSSERVICE_H
#define PHYSICSSERVICE_H

#include <QObject>

class PhysicsService : public QObject
{
    Q_OBJECT
public:
    explicit PhysicsService(QObject *parent = nullptr);

signals:

};

#endif // PHYSICSSERVICE_H
