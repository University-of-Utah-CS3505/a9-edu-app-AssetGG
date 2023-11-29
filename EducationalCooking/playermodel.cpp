#include "playermodel.h"
#include "ingredient.h"
#include "recipecardwidget.h"
#include "recipe.h"
#include <vector>

using std::vector;

PlayerModel::PlayerModel(Physics &physics, QObject *parent)
    : QObject{parent}
    , physics{physics}
{
    currentlyClickedOn = nullptr;
    vector<Ingredient> base;
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

void PlayerModel::setupScene(Recipe &recipe)
{
    setupWalls();

    for (Ingredient &ingredient : recipe.getAvaliableIngredients()) {
        setupIngredient(ingredient);
    }
    //Physics::PhysicsObject *obj = physicsObjects.at("tomato");

    physics.start();
    // set up ingredient collision objects
}

void PlayerModel::setupWalls()
{
    auto rightWallShape = Physics::createBoxShape(10.0, 640.0);
    auto leftWallShape = Physics::createBoxShape(10.0, 640.0);
    auto topWallShape = Physics::createBoxShape(640.0, 10.0);
    auto bottomWallShape = Physics::createBoxShape(640.0, 10.0);

    physics.registerStaticObject("rightWall", &rightWallShape, 640.0, 320.0);
    physics.registerStaticObject("leftWall", &leftWallShape, 0.0, 320.0);
    physics.registerStaticObject("topWall", &topWallShape, 320.0, -15.0);
    physics.registerStaticObject("bottomWall", &bottomWallShape, 320.0, 640.0);
}

void PlayerModel::setupIngredient(Ingredient &ingredient)
{
    QRect spriteBounds = ingredient.GetRect();
    float radius = std::min(spriteBounds.width(), spriteBounds.height()) / 2.0;
    auto circle = Physics::createCircleShape(radius);
    auto obj = physics.registerDynamicObject(ingredient.GetName(),
                                             &circle,
                                             ingredient.locX,
                                             ingredient.locY);

    obj.fixture->SetFriction(0.2);
    obj.fixture->SetRestitution(0.1);
    //obj.body->SetLinearVelocity(b2Vec2(0.0, -50.0));
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
