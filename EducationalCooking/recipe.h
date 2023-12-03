/*
 * Name: everyone
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: This class outlines the functionality of a recipe object.
 */

#ifndef RECIPE_H
#define RECIPE_H

#include <QObject>
#include <QImage>
#include <vector>
#include "ingredient.h"
#include "comparisoningredient.h"

class Recipe
{
public:
    Recipe(std::string, std::vector<ComparisonIngredient>, std::vector<ComparisonIngredient>, std::vector<Ingredient>, QImage);
    std::vector<ComparisonIngredient> getBaseIngredients();
    std::vector<ComparisonIngredient> getBonusIngredients();
    std::vector<Ingredient> getAvaliableIngredients();
    std::string getRecipeName();
    QImage helpSpriteSmall;
    QImage helpSpriteLarge;
    QImage getLargeHelpSprite();
    QImage getSmallHelpSprite();
    int getXLocation();
    int getYLocation();

private:
    // ingredients for the bare bones food
    std::vector<ComparisonIngredient> baseIngredients;

    // ingredients that will give bonus points
    std::vector<ComparisonIngredient> bonusIngredients;

    // all avaliable ingredients (including base/bonus/red herring ones)
    std::vector<Ingredient> avaliableIngredients;
    std::string recipeName;

    QImage image;

    // The xLocation and yLocation of the recipeHelp sprite
    int xLoc, yLoc;
};

#endif // RECIPE_H
