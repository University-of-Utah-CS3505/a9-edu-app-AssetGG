/*
 * Name: Kazimar Guenther, Yukon Zipperer
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: This class handles the data used for comparing
 * final ingredient with current ingredient
 * Reviewed By: Asset Yerzhigit
 */

#include "comparisoningredient.h"
#include "ingredient.h"

ComparisonIngredient::ComparisonIngredient(std::string foodName, bool isCut, bool isCooked)
{
    cut = isCut;
    cooked = isCooked;
    name = foodName;
}

ComparisonIngredient::ComparisonIngredient()
{
    cut = false;
    cooked = false;
    name = "default";
}

std::string ComparisonIngredient::getName() const
{
    return name;
}

bool ComparisonIngredient::isCooked() const
{
    return cooked;
}

bool ComparisonIngredient::isCut() const
{
    return cut;
}

bool ComparisonIngredient::legalIngredient(Ingredient ingredient)
{
    if(ingredient.isCut() != cut || ingredient.isCooked() != cooked)
        return false;

    return true;
}
