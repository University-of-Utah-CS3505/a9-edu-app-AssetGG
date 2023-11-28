#ifndef RECIPE_H
#define RECIPE_H

#include <QObject>
#include "ingredient.h"
#include <vector>

class Recipe
{
public:
    Recipe(std::string, std::vector<Ingredient>);
    std::vector<Ingredient> getIngredients();
    std::string getRecipeName();

private:
    std::vector<Ingredient> ingredients;
    std::string recipeName;
};

#endif // RECIPE_H
