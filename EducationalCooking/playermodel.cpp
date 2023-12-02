#include "playermodel.h"
#include "ingredient.h"
#include "recipe.h"
#include "recipecardwidget.h"
#include "tools.h"
#include <vector>

using std::vector;

PlayerModel::PlayerModel(Physics &physics, QObject *parent)
    : QObject{parent}
    , physics{physics}
{
    currentlyClickedOn = nullptr;
    vector<Ingredient> base;
}

// incomplete
// doesn't have proper png
// booleans incomplete
void PlayerModel::setupRecipes(){
    QString folder = ":/sprites/Sprites/";

    vector<Ingredient> avaliable;
    vector<Ingredient> base;
    vector<Ingredient> bonus;

    // std::string name, QImage baseImage, QImage cutImage, QImage cookedImage, bool cuttable, bool cookable, int x, int y)

    /*
     * Spaghetti
        base: noodles, sauce
        bonus: meatballs, chicken, cheese
        fake: milk, ketchup
    */
    base.push_back(Ingredient("spaghetti", QImage(folder + "Tomato.png"), QImage(), QImage(), false, true, 0, 0));
    base.push_back(Ingredient("tomato sauce", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    bonus.push_back(Ingredient("meatballs", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    bonus.push_back(Ingredient("chicken", QImage(folder + "Tomato.png"), QImage(), QImage(), true, true, 0, 0));
    bonus.push_back(Ingredient("cheese", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.insert(avaliable.end(), bonus.begin(), bonus.end());
    avaliable.insert(avaliable.end(), base.begin(), base.end());
    avaliable.push_back(Ingredient("meatballs", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    recipes.push_back(Recipe("spaghetti", base, bonus, avaliable));

    /*
     * Salad
        base: lettuce, salad dressing
        bonus: cheese, tomato, cucumber
        fake: sugar, ketchup
     */

    base.push_back(Ingredient("lettuce", QImage(folder + "Tomato.png"), QImage(), QImage(), false, true, 0, 0));
    base.push_back(Ingredient("salad dressing", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    bonus.push_back(Ingredient("tomato", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    bonus.push_back(Ingredient("cucumber", QImage(folder + "Tomato.png"), QImage(), QImage(), true, true, 0, 0));
    bonus.push_back(Ingredient("cheese", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.insert(avaliable.end(), bonus.begin(), bonus.end());
    avaliable.insert(avaliable.end(), base.begin(), base.end());
    avaliable.push_back(Ingredient("sugar", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("ketchup", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    recipes.push_back(Recipe("salad", base, bonus, avaliable));

    /*
     * Pizza
        base: dough, cheese, sausage, tomato sauce
        bonus: peppers, chiles, or onion
        fake: carrots, honey, ketchup
     */
    base.push_back(Ingredient("dough", QImage(folder + "Tomato.png"), QImage(), QImage(), false, true, 0, 0));
    base.push_back(Ingredient("tomato sauce", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    base.push_back(Ingredient("cheese", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    base.push_back(Ingredient("sausage", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    bonus.push_back(Ingredient("peppers", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    bonus.push_back(Ingredient("chiles", QImage(folder + "Tomato.png"), QImage(), QImage(), true, true, 0, 0));
    bonus.push_back(Ingredient("onion", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.insert(avaliable.end(), bonus.begin(), bonus.end());
    avaliable.insert(avaliable.end(), base.begin(), base.end());
    avaliable.push_back(Ingredient("carrots", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("honey", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("ketchup", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    recipes.push_back(Recipe("pizza", base, bonus, avaliable));

    /*
     *
        Soup
        base: tomato sauce (is this considered tomatoes?), green chili, beet
        bonus: peppers, chiles, onion, or mushrooms
        fake: tuna, carrots, cabbage
     */
    base.push_back(Ingredient("green chili", QImage(folder + "Tomato.png"), QImage(), QImage(), false, true, 0, 0));
    base.push_back(Ingredient("tomato sauce", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    base.push_back(Ingredient("beet", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    base.push_back(Ingredient("chiles", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    bonus.push_back(Ingredient("peppers", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    bonus.push_back(Ingredient("mushrooms", QImage(folder + "Tomato.png"), QImage(), QImage(), true, true, 0, 0));
    bonus.push_back(Ingredient("onion", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.insert(avaliable.end(), bonus.begin(), bonus.end());
    avaliable.insert(avaliable.end(), base.begin(), base.end());
    avaliable.push_back(Ingredient("carrots", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("tuna", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("cabbage", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    recipes.push_back(Recipe("soup", base, bonus, avaliable));

    /*
     * Hamburger
        base: Bun, patty, cheese, lettuce, tomato
        bonus: onion, ketchup, or avocado
        fake: cucumber, blueberry, chocolate, cod, cabbage, honey, tuna
    */
    base.push_back(Ingredient("bun", QImage(folder + "Tomato.png"), QImage(), QImage(), false, true, 0, 0));
    base.push_back(Ingredient("patty", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    base.push_back(Ingredient("cheese", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    base.push_back(Ingredient("lettuce", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    base.push_back(Ingredient("tomato", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    bonus.push_back(Ingredient("onion", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    bonus.push_back(Ingredient("ketchup", QImage(folder + "Tomato.png"), QImage(), QImage(), true, true, 0, 0));
    bonus.push_back(Ingredient("avocado", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.insert(avaliable.end(), bonus.begin(), bonus.end());
    avaliable.insert(avaliable.end(), base.begin(), base.end());
    avaliable.push_back(Ingredient("cucumber", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("blueberry", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("chocolate", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("cabbage", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("cod", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("honey", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("tuna", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    recipes.push_back(Recipe("hamburger", base, bonus, avaliable));

    /*
     *  Pancake
        base: milk, eggs, flour, sugar, bUtTeR
        bonus points: chocolate, syrup, strawberry
        fake: carrots, pumpkin, cabbage, cucumber, meatballs, ketchup, tuna,
     */
    base.push_back(Ingredient("milk", QImage(folder + "Tomato.png"), QImage(), QImage(), false, true, 0, 0));
    base.push_back(Ingredient("eggs", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    base.push_back(Ingredient("flour", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    base.push_back(Ingredient("sugar", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    base.push_back(Ingredient("butter", QImage(folder + "Tomato.png"), QImage(), QImage(), false, false, 0, 0));
    bonus.push_back(Ingredient("chocolate", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    bonus.push_back(Ingredient("syrup", QImage(folder + "Tomato.png"), QImage(), QImage(), true, true, 0, 0));
    bonus.push_back(Ingredient("strawberry", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.insert(avaliable.end(), bonus.begin(), bonus.end());
    avaliable.insert(avaliable.end(), base.begin(), base.end());
    avaliable.push_back(Ingredient("carrots", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("pumpkin", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("cabbage", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("cucumber", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("meatballs", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("ketchup", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("tuna", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    recipes.push_back(Recipe("pancake", base, bonus, avaliable));
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

void PlayerModel::setupScene(Recipe &recipe, std::map<std::string, Tool> &tools)
{
    setupWalls();

    for (Ingredient &ingredient : recipe.getAvaliableIngredients()) {
        setupIngredient(ingredient);
    }

    for (auto &[toolName, tool] : tools) {
        setupCookingTool(tool);
    }

    physics.start();
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
    QRect spriteBounds = ingredient.GetImage().rect();
    float radius = std::min(spriteBounds.width(), spriteBounds.height()) / 2.0;
    auto circle = Physics::createCircleShape(radius);
    auto obj = physics.registerDynamicObject(ingredient.GetName(),
                                             &circle,
                                             ingredient.locX,
                                             ingredient.locY);

    b2Filter collisionFilter;
    // Walls are 0x0001 (by default), Ingredients are 0x0002, tools are 0x0004
    collisionFilter.categoryBits = 0x0002;
    // black magic meaning it can collide with walls or ingredients, but not tools.
    collisionFilter.maskBits = 0x0001 | 0x0002;

    obj.fixture->SetFriction(0.2);
    obj.fixture->SetRestitution(0.1);
    obj.fixture->SetFilterData(collisionFilter);

    obj.body->SetLinearDamping(5.0);
}

void PlayerModel::setupCookingTool(Tool tool)
{
    // create a physics object for the tool
    auto boxShape = Physics::createBoxShape(tool.GetImage().width(), tool.GetImage().height());

    b2Filter collisionFilter;
    // Walls are 0x0001, Ingredients are 0x0002, tools are 0x0004
    collisionFilter.categoryBits = 0x0004;
    // black magic meaning it can collide with walls or tools, but not ingredients.
    collisionFilter.maskBits = 0x0001 | 0x0004;

    Physics::PhysicsObject *obj = nullptr;
    if (tool.IsMovable()) {
        obj = &physics.registerDynamicObject(tool.GetName(), &boxShape, tool.locX, tool.locY);

    } else {
        obj = &physics.registerStaticObject(tool.GetName(), &boxShape, tool.locX, tool.locY);
    }

    obj->body->SetLinearDamping(15.0);
    obj->fixture->SetFilterData(collisionFilter);
}

/*
Easy Recipes- 7 options
Spaghetti
base: noodles, sauce
bonus: meatballs, chicken, cheese
fake: milk, ketchup

Salad
base: lettuce, salad dressing
bonus: cheese, tomato, cucumber
fake: sugar, ketchup
-----------------------------------
Intermediate Recipes- 10 options

Pizza
base: dough, cheese, sausage, tomato sauce(or is this tomatoes?)
bonus: peppers, chiles, or onion
fake: carrots, honey, ketchup

Soup
base: tomato sauce (is this considered tomatoes?), green chili, beet
bonus: peppers, chiles, onion, or mushrooms
fake: tuna, carrots, cabbage
-----------------------------------
Hard Recipes- 15 options

Hamburger
base: Bun, patty, cheese, lettuce, tomato
bonus: onion, ketchup, or avocado
fake: cucumber, blueberry, chocolate, cod, cabbage, honey, tuna

Pancake
base: milk, eggs, flour, sugar, bUtTeR
bonus points: chocolate, syrup, strawberry
fake: carrots, pumpkin, cabbage, cucumber, meatballs, ketchup, tuna,
*/
