#include "playermodel.h"
#include "recipe.h"
#include "ingredient.h"
#include <vector>

using std::vector;

PlayerModel::PlayerModel(QObject *parent)
    : QObject{parent}
{
    currentlyClickedOn = nullptr;
    vector<Ingredient> base;

}

/*
Easy Recipes- 7 options
Spaghetti
base: noodles, sauce
bonus: meatballs, chicken, cheese
fake: milk, carrots

Salad
base: lettuce, salad dressing
bonus: cheese, tomato, cucumber
fake: sugar, ketchup
-----------------------------------
Intermediate Recipes- 10 options

Pizza
base: dough, cheese, sausage, tomato sauce(or is this tomatoes?)
bonus: peppers, chiles, or onion
fake: carrots, soy sauce, ketchup

Soup
base: tomato sauce (is this considered tomatoes?), green chili, radish
bonus: peppers, chiles, onion, or mushrooms
fake: olives, carrots, cabbage
-----------------------------------
Hard Recipes- 15 options

Hamburger
base: Bun, patty, cheese, lettuce, tomato
bonus: onion, ketchup, or avocado
fake: cucumber, blueberry, chocolate, cod, cabbage, pumpkin, tuna

Pancake
base: milk, eggs, flour, sugar, bUtTeR
bonus points: chocolate, syrup, strawberry
fake: carrots, pumpkin, cabbage, cucumber, soy sauce, ketchup, sirracha,
*/
