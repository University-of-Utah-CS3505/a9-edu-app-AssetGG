#include "playermodel.h"

PlayerModel::PlayerModel(QObject *parent)
    : QObject{parent}
{
    // currentlyClickedOn = NULL;
}

void PlayerModel::didClickOnIngredient(QPoint clickLocation)
{
    for (Ingredient ingredient : ingredients)
        if (ingredient.locX == clickLocation.x() || ingredient.locY == clickLocation.y())
            currentlyClickedOn = ingredient;
}

void PlayerModel::notHoldingIngredient(QPoint dropLocation)
{
    //    if (currentlyClickedOn != NULL)
    //    {
    //        currentlyClickedOn.x = dropLocation.x();
    //        currentlyClickedOn.y = dropLocation.y();
    //        currentlyClickedOn = NULL;
    //    }
}

void PlayerModel::movingIngredientToPoint(QPoint moveLocation)
{
    /*f (currentlyClickedOn != NULL)
    {
        currentlyClickedOn.x = moveLocation.x();
        currentlyClickedOn.y = moveLocation.y();
    }*/
}
