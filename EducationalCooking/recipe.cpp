#include "recipe.h"
#include "comparisoningredient.h"

using std::string;
using std::vector;

Recipe::Recipe(string name,
               vector<ComparisonIngredient> baseList,
               vector<ComparisonIngredient> bonusList,
               vector<Ingredient> avaliableList)
    : baseIngredients(baseList)
    , bonusIngredients(bonusList)
    , avaliableIngredients(avaliableList)
    , recipeName(name)
{
    helpSpriteSmall = QImage(":/sprites/Sprites/recipeHelp.png");
    helpSpriteLarge = QImage(":/sprites/Sprites/fullSizeRecipeHelp.png");
}

Recipe::Recipe()
    : xLoc(0)
    , yLoc(0)
{}

vector<ComparisonIngredient> Recipe::getBaseIngredients() const
{
    return baseIngredients;
}

vector<ComparisonIngredient> Recipe::getBonusIngredients() const
{
    return bonusIngredients;
}

vector<Ingredient> Recipe::getAvaliableIngredients() const
{
    return avaliableIngredients;
}

string Recipe::getRecipeName() const
{
    return recipeName;
}

QImage Recipe::getSmallHelpSprite() const
{
    return helpSpriteSmall;
}

QImage Recipe::getLargeHelpSprite() const
{
    return helpSpriteLarge;
}

int Recipe::getXLocation() const
{
    return xLoc;
}

int Recipe::getYLocation() const
{
    return yLoc;
}
