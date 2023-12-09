/*
 * Name: Everyone
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: This class handles functionality for recipe objects.
 * Reviewed By: David Cosby
 */

#include "recipe.h"
#include "comparisoningredient.h"

using std::string;
using std::vector;

Recipe::Recipe(string name,
               vector<ComparisonIngredient> baseList,
               vector<ComparisonIngredient> bonusList,
               vector<Ingredient> avaliableList):
    baseIngredients(baseList),
    bonusIngredients(bonusList),
    avaliableIngredients(avaliableList),
    recipeName(name)
{
    helpSpriteSmall = QImage(":/sprites/Sprites/recipeHelp.png");
    helpSpriteLarge = QImage(":/sprites/Sprites/fullSizeRecipeHelp.png");
}

Recipe::Recipe()
    : xLocation(0)
    , yLocation(0)
{

}

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
    return xLocation;
}

int Recipe::getYLocation() const
{
    return yLocation;
}
