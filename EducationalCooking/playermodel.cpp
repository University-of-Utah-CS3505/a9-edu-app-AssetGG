#include "playermodel.h"
#include "recipe.h"
#include "ingredient.h"
#include "recipecardwidget.h"
#include <vector>

using std::vector;

PlayerModel::PlayerModel(QObject *parent)
    : QObject(parent), currentlyClickedOn(nullptr)
{
    // Todo: Initialize other properties

}

void PlayerModel::setCurrentRecipe(const QString& recipe)
{
    currentRecipe = recipe;
    emit selectedRecipeChanged(currentRecipe); // May or may not be useful, as user cannot change recipe mid game
}

const QString& PlayerModel::getCurrentRecipe() const
{
    return currentRecipe;
}

void PlayerModel::handleRecipeClicked(const QString &recipeName)
{
    qDebug() << "Recipe clicked:" << recipeName;
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
