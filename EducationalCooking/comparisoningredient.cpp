#include "comparisoningredient.h"
#include "ingredient.h"

// Constructor for ComparisonIngredient.
ComparisonIngredient::ComparisonIngredient(std::string foodName, bool isCut, bool isCooked)
{
    cut = isCut;
    cooked = isCooked;
    name = foodName;
}

// Default Constructor
ComparisonIngredient::ComparisonIngredient()
{
    cut = false;
    cooked = false;
    name = "default";
}

// Getter for the name of ComparisonIngredient.
std::string ComparisonIngredient::GetName() const {
    return name;
}

// Getter for cooked of ComparisonIngredient
bool ComparisonIngredient::IsCooked() const
{
    return cooked;
}

// Getter for the cut of ComparisonIngrdient
bool ComparisonIngredient::IsCut() const
{
    return cut;
}

// Compares the state of ingredient sent in to this ComparisonIngredient's state.
bool ComparisonIngredient::legalIngredient(Ingredient ingredient)
{
    if(ingredient.IsCut() != cut || ingredient.IsCooked() != cooked)
    {
        return false;
    }

    return true;
}
