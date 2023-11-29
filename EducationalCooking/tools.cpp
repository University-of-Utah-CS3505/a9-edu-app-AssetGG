#include "tools.h"
#include <string>
#include <QMouseEvent>

Tools::Tools(CookingToolType type) : toolType(type)
{
    // Empty constructor
    // Might need to rethink this
}

void Tools::ProcessIngredient(Ingredient& ingredient)
{
    switch (toolType)
    {
    case CookingToolType::CuttingBoard:
        // Might needd to move the if statements like is cookable/cuttable here from ingredients class
        ingredient.Cut();
        break;

    case CookingToolType::Pot:
        ingredient.Cooked();
        break;

    case CookingToolType::FryingPan:
        // Add frying pan logic
        break;

     // Add more cases for other cooking tools

    default:
        // TODO: think about the default case
        break;
    }
}
