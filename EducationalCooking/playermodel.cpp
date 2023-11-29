#include "playermodel.h"

PlayerModel::PlayerModel(QObject *parent)
    : QObject{parent}
{
    currentlyClickedOn = nullptr;
}

void PlayerModel::didClickOnIngredient(QPoint clickLocation)
{
    for (Ingredient ingredient : ingredients)
        if (ingredient.locX == clickLocation.x() || ingredient.locY == clickLocation.y())
            currentlyClickedOn = ingredient;
}

void PlayerModel::dropIngredient(QPoint dropLocation)
{
    if (currentlyClickedOn != nullptr)
    {
        currentlyClickedOn->x = dropLocation.x();
        currentlyClickedOn->y = dropLocation.y();
        currentlyClickedOn = nullptr;
    }
}

void PlayerModel::moveIngredientToPoint(QPoint moveLocation)
{
    if (currentlyClickedOn != nullptr)
    {
        currentlyClickedOn->x = moveLocation.x();
        currentlyClickedOn->y = moveLocation.y();

        emit updateIngredientOnScreen(currentlyClickedOn->ingredientImage, currentlyClickedOn->x, currentlyClickedOn->y);
    }
}
