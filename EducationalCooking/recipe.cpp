#include "recipe.h"
#include <string>
#include <vector>
#include "comparisoningredient.h"

using std::vector;
using std::string;

Recipe::Recipe(string name, vector<ComparisonIngredient> baseList, vector<ComparisonIngredient> bonusList, vector<Ingredient> avaliableList, QImage image)
{
    recipeName = name;
    baseIngredients.swap(baseList);
    bonusIngredients.swap(bonusList);
    avaliableIngredients.swap(avaliableList);
    this->image = image;
    helpSpriteSmall = QImage(":/sprites/Sprites/recipeHelp.png");
    helpSpriteLarge = QImage(":/sprites/Sprites/fullSizeRecipeHelp.png");
}

vector<ComparisonIngredient> Recipe::getBaseIngredients(){
    return baseIngredients;
}

vector<ComparisonIngredient> Recipe::getBonusIngredients()
{
    return bonusIngredients;
}

vector<Ingredient> Recipe::getAvaliableIngredients(){
    return avaliableIngredients;
}

string Recipe::getRecipeName(){
    return recipeName;
}

QImage Recipe::getSmallHelpSprite()
{
    return helpSpriteSmall;
}

QImage Recipe::getLargeHelpSprite()
{
    return helpSpriteLarge;
}

int Recipe::getXLocation()
{
    return xLoc;
}

int Recipe::getYLocation()
{
    return yLoc;
}
