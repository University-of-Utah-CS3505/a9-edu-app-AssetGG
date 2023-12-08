/*
 * Name: Everyone
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: This class outlines the functionality of a recipe object.
 * Reviewed By: David Cosby
 */

#ifndef RECIPE_H
#define RECIPE_H

#include <QImage>
#include <QObject>
#include "comparisoningredient.h"
#include "ingredient.h"

class Recipe
{
public:
    /// Constructor that takes in our base, bonus, and avaliable ingredients
    Recipe(std::string,
           std::vector<ComparisonIngredient>,
           std::vector<ComparisonIngredient>,
           std::vector<Ingredient>);
    /// Description: Default constructor.
    Recipe();

    /// Getter method for vector of base ingredients
    std::vector<ComparisonIngredient> getBaseIngredients() const;

    /// Getter method for vector of bonus ingredients
    std::vector<ComparisonIngredient> getBonusIngredients() const;

    /// Getter method for avaliable ingredients
    std::vector<Ingredient> getAvaliableIngredients() const;

    /// Getter method for recipe name
    std::string getRecipeName() const;

    /// Getter method for help sprite when clicked
    QImage getLargeHelpSprite() const;

    /// Getter method for help sprite
    QImage getSmallHelpSprite() const;

    /// Getter method for recipe help's x location
    int getXLocation() const;

    /// Getter method for recipe help's y location
    int getYLocation() const;

private:
    /// ingredients for the bare bones food
    std::vector<ComparisonIngredient> baseIngredients;
    /// ingredients that will give bonus points
    std::vector<ComparisonIngredient> bonusIngredients;
    /// all avaliable ingredients (including base/bonus/red herring ones)
    std::vector<Ingredient> avaliableIngredients;

    std::string recipeName;
    QImage helpSpriteSmall;
    QImage helpSpriteLarge;

    /// The xLocation and yLocation of the recipeHelp sprite
    int xLocation, yLocation;
};

#endif // RECIPE_H
