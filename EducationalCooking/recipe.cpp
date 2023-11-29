#include "recipe.h"
#include <string>
#include <vector>

using std::vector;
using std::string;

Recipe::Recipe(string name, vector<Ingredient> baseList, vector<Ingredient> bonusList, vector<Ingredient> avaliableList)
{
    recipeName = name;
    baseIngredients.swap(baseList);
    bonusIngredients.swap(bonusList);
    avaliableIngredients.swap(avaliableList);
}

vector<Ingredient> Recipe::getBaseIngredients(){
    return baseIngredients;
}

vector<Ingredient> Recipe::getBonusIngredients(){
    return bonusIngredients;
}

vector<Ingredient> Recipe::getAvaliableIngredients(){
    return avaliableIngredients;
}

string Recipe::getRecipeName(){
    return recipeName;
}
