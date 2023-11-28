#include "recipe.h"
#include <string>
#include <vector>


Recipe::Recipe(std::string name, std::vector<Ingredient> list)
{
    recipeName = name;
    ingredients.clear();
    foreach (Ingredient n, list) {
        ingredients.push_back(n);
    }
}

std::vector<Ingredient> Recipe::getIngredients(){
    return ingredients;
}


std::string Recipe::getRecipeName(){
    return recipeName;
}
