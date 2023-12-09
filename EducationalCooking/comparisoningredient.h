/*
 * Name: Kazimar Guenther, Yukon Zipperer
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: This class is used for comparing
 * final ingredient with current ingredient
 * Reviewed By: Asset Yerzhigit
 */

#ifndef COMPARISONINGREDIENT_H
#define COMPARISONINGREDIENT_H

#include "ingredient.h"
#include <string>

class ComparisonIngredient
{
public:

    /// Builds a comparison object with the given name and sets the cut and cooked properties
    ComparisonIngredient(std::string, bool, bool);
    ComparisonIngredient();

    /// Compares the state of ingredient sent in to this ComparisonIngredient's state.
    bool legalIngredient(Ingredient);

    /// Getter for the name of ComparisonIngredient.
    std::string GetName() const;

    /// Getter for cooked of ComparisonIngredient
    bool IsCooked() const;

    /// Getter for the cut of ComparisonIngrdient
    bool IsCut() const;

private:
    bool cut;
    bool cooked;
    std::string name;
};
#endif // COMPARISONINGREDIENT_H
