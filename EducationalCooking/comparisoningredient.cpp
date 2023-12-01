#include "comparisoningredient.h"
#include "ingredient.h"

ComparisonIngredient::ComparisonIngredient(bool isCut, bool isCooked)
{
    cut = isCut;
    cooked = isCooked;
}

ComparisonIngredient::ComparisonIngredient()
{
    cut = false;
    cooked = false;
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
