#include "playermodel.h"

PlayerModel::PlayerModel(QObject *parent)
    : QObject{parent}
{
    currentlyClickedOn = nullptr;
}

