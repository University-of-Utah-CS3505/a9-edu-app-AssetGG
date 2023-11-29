#ifndef TOOLS_H
#define TOOLS_H

#include <QImage>
#include <QString>
#include "ingredient.h"

enum class CookingToolType
{
    CuttingBoard,
    FryingPan,
    Pot,
    // TODO: Add other tools
};

class Tools
{
public:
    Tools(CookingToolType type);
    void ProcessIngredient(Ingredient& ingredient);

private:
    CookingToolType toolType;
};

#endif // TOOLS_H
