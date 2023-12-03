#ifndef COMPARISONINGREDIENT_H
#define COMPARISONINGREDIENT_H

#include "ingredient.h"
#include <string>

class ComparisonIngredient
{
public:
    ComparisonIngredient(std::string, bool, bool);
    ComparisonIngredient();
    bool legalIngredient(Ingredient);
private:
    bool cut;
    bool cooked;
    std::string name;
};
#endif // COMPARISONINGREDIENT_H
