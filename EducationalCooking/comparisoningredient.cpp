#include "comparisoningredient.h"
#include "ingredient.h"
#include <string>

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

std::string ComparisonIngredient::GetName() const {
    return name;
}

bool ComparisonIngredient::IsCooked() const
{
    return cooked;
}
bool ComparisonIngredient::IsCut() const
{
    return cut;
}

bool ComparisonIngredient::legalIngredient(Ingredient ingredient)
{
    if(ingredient.IsCut() != cut || ingredient.IsCooked() != cooked)
    {
        return false;
    }

    if (ingredient.IsBurned())
    {
        return false;
    }

    return true;
}
