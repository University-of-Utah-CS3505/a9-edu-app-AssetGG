#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "playermodel.h"
#include "playerview.h"

class Controller
{
public:
    Controller(PlayerModel &model, PlayerView &view);
};

#endif // CONTROLLER_H
