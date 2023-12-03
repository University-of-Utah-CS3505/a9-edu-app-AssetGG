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
    Recipe();
    std::vector<ComparisonIngredient> getBaseIngredients() const;
    std::vector<ComparisonIngredient> getBonusIngredients() const;
    std::vector<Ingredient> getAvaliableIngredients() const;
    std::string getRecipeName() const;
    QImage helpSpriteSmall;
    QImage helpSpriteLarge;
    QImage getLargeHelpSprite() const;
    QImage getSmallHelpSprite() const;
    int getXLocation() const;
    int getYLocation() const;

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
