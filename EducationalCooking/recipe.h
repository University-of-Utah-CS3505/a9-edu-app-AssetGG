/*
 * Name: everyone
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: This class outlines the functionality of a recipe object.
 */

#ifndef RECIPE_H
#define RECIPE_H

#include <QObject>
#include "ingredient.h"
#include <vector>

class Recipe
{
public:
    Recipe(std::string, std::vector<Ingredient>, std::vector<Ingredient>, std::vector<Ingredient>);
    std::vector<Ingredient> getBaseIngredients();
    std::vector<Ingredient> getBonusIngredients();
    std::vector<Ingredient> getAvaliableIngredients();
    std::string getRecipeName();

private:
    // ingredients for the bare bones food
    std::vector<Ingredient> baseIngredients;

    // ingredients that will give bonus points
    std::vector<Ingredient> bonusIngredients;

    // all avaliable ingredients (including base/bonus/red herring ones)
    std::vector<Ingredient> avaliableIngredients;
    std::string recipeName;
};

#endif // RECIPE_H
