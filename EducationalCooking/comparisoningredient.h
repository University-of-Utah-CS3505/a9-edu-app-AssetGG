#ifndef COMPARISONINGREDIENT_H
#define COMPARISONINGREDIENT_H

#include "ingredient.h"

class ComparisonIngredient
{
public:
    ComparisonIngredient(bool, bool);
    ComparisonIngredient();
    bool legalIngredient(Ingredient);
private:
    bool cut;
    bool cooked;
};
#endif // COMPARISONINGREDIENT_H
