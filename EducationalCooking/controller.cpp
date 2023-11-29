#include "controller.h"
#include "playermodel.h"
#include "playerview.h"

Controller::Controller(PlayerModel &model, PlayerView &view)
{
    connect(&view, &PlayerView::didClickOnIngredient, &model, &PlayerModel::didClickOnIngredient);
    connect(&view, &PlayerView::dropIngredient, &model, &PlayerModel::dropIngredient);
    connect(&view, &PlayerView::updateIngredientPosition, &model, &PlayerModel::moveIngredientToPoint);
    connect(&model, &PlayerModel::updateClickedIngredient, &view, &PlayerView::updateClickedIngredient);
}
