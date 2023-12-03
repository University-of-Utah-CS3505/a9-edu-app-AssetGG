#include "playermodel.h"
#include "ingredient.h"
#include "recipe.h"
#include "recipecardwidget.h"
#include "tools.h"
#include <vector>
#include "comparisoningredient.h"

using std::vector;

PlayerModel::PlayerModel(Physics &physics, QObject *parent)
    : QObject{parent}
    , physics{physics}
{
    currentlyClickedOn = nullptr;
    vector<Ingredient> base;
    finalScore = 0;
}

// incomplete
// doesn't have proper png
// booleans incomplete
void PlayerModel::setupRecipes(){
    QString folder = ":/sprites/Sprites/";

    vector<Ingredient> avaliable;
    vector<ComparisonIngredient> base;
    vector<ComparisonIngredient> bonus;

    // std::string name, QImage baseImage, QImage cutImage, QImage cookedImage, bool cuttable, bool cookable, int x, int y)

    /*
     * Spaghetti
        base: noodles, sauce
        bonus: meatballs, chicken, cheese
        fake: milk, ketchup
    */
    base.push_back(ComparisonIngredient("spaghetti", false, true));
    base.push_back(ComparisonIngredient("tomato sauce", false, false));
    bonus.push_back(ComparisonIngredient("meatballs", false, true));
    bonus.push_back(ComparisonIngredient("chicken", true, true));
    bonus.push_back(ComparisonIngredient("cheese", false, false));

    avaliable.push_back(Ingredient("noodles", QImage(folder + "Plain Pasta.png"),
                                   QImage(), QImage(), false, true, 0, 0));
    avaliable.push_back(Ingredient("tomato sauce", QImage(folder + "Tomato Sauce.png"),
                                   QImage(), QImage(), false, false, 0, 0));
    avaliable.push_back(Ingredient("meatballs", QImage(folder + "Meatball.png"),
                                   QImage(), QImage(), false, true, 0, 0));
    avaliable.push_back(Ingredient("chicken", QImage(folder + "Raw Chicken.png"),
                                   QImage(), QImage(folder + "Cooked Chicken.png"), true, true, 0, 0));
    avaliable.push_back(Ingredient("cheese", QImage(folder + "Cheese Slice.png"),
                                   QImage(folder + "Cheddar"), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("milk", QImage(folder + "Milk.png"), QImage(), QImage(), false, true, 0, 0));
    // missing
    avaliable.push_back(Ingredient("ketchup", QImage(folder + "Tomato.png"), QImage(), QImage(), true, false, 0, 0));
    recipes.push_back(Recipe("spaghetti", base, bonus, avaliable, QImage(folder)));

    /*
     * Salad
        base: lettuce, salad dressing
        bonus: cheese, tomato, cucumber
        fake: sugar, ketchup
     */

    base.push_back(ComparisonIngredient("lettuce", true, false));
    base.push_back(ComparisonIngredient("salad dressing", false, false));
    bonus.push_back(ComparisonIngredient("tomato", true, false));
    bonus.push_back(ComparisonIngredient("cucumber", true, false));
    bonus.push_back(ComparisonIngredient("cheese", false, false));

    // missing
    avaliable.push_back(Ingredient("lettuce", QImage(folder + "Tomato.png"),
                                   QImage(), QImage(), true, false, 0, 0));
    //misisng
    avaliable.push_back(Ingredient("salad dressing", QImage(folder + "Tomato.png"),
                                   QImage(), QImage(), false, false, 0, 0));
    avaliable.push_back(Ingredient("tomato", QImage(folder + "Tomato.png"),
                                   QImage(), QImage(), true, true, 0, 0));
    avaliable.push_back(Ingredient("cucumber", QImage(folder + "Cucumber.png"),
                                   QImage(folder + "Cucumber Slices.png"), QImage(), true, true, 0, 0));
    avaliable.push_back(Ingredient("cheese", QImage(folder + "Cheese Slice.png"),
                                   QImage(folder + "Cheddar"), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("sugar", QImage(folder + "Sugar.png"),
                                   QImage(), QImage(), false, false, 0, 0));
    // missing
    avaliable.push_back(Ingredient("ketchup", QImage(folder + "Tomato.png"),
                                   QImage(), QImage(), false, false, 0, 0));
    recipes.push_back(Recipe("salad", base, bonus, avaliable, QImage()));

    /*
     * Pizza
        base: dough, cheese, sausage, tomato sauce
        bonus: peppers, chiles, or onion
        fake: carrots, honey, ketchup
     */
    base.push_back(ComparisonIngredient("dough", false, true));
    base.push_back(ComparisonIngredient("tomato sauce", false, true));
    base.push_back(ComparisonIngredient("cheese", false, true));
    base.push_back(ComparisonIngredient("sausage", true, true));
    bonus.push_back(ComparisonIngredient("peppers", true, true));
    bonus.push_back(ComparisonIngredient("chiles", true, true));
    bonus.push_back(ComparisonIngredient("onion", true, true));

    // missing
    avaliable.push_back(Ingredient("dough", QImage(folder + "Tomato.png"),
                                   QImage(), QImage(), false, true, 0, 0));
    avaliable.push_back(Ingredient("tomato sauce", QImage(folder + "Tomato Sauce.png"),
                                   QImage(), QImage(), false, false, 0, 0));
    avaliable.push_back(Ingredient("cheese", QImage(folder + "Cheese Slice.png"),
                                   QImage(folder + "Cheddar"), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("sausage", QImage(folder + "Raw Sausage.png"),
                                   QImage(folder + "Half Pepperoni.png"),
                                   QImage(folder + "Cooked Sausage"), true, true, 0, 0));
    // missing
    avaliable.push_back(Ingredient("bell peppers", QImage(folder + "Tomato.png"),
                                   QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("chiles", QImage(folder + "Red Chili Pepper.png"),
                                   QImage(), QImage(), true, true, 0, 0));
    avaliable.push_back(Ingredient("onion", QImage(folder + "Brown Onion.png"),
                                   QImage(folder + "Half brown onion"), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("carrots", QImage(folder + "Carrot.png"),
                                   QImage(folder + "Sliced Carrot.png"), QImage(), true, true, 0, 0));
    avaliable.push_back(Ingredient("honey", QImage(folder + "Honey.png"),
                                   QImage(), QImage(), true, false, 0, 0));
    // missing
    avaliable.push_back(Ingredient("ketchup", QImage(folder + "Tomato.png"),
                                   QImage(), QImage(), true, false, 0, 0));
    recipes.push_back(Recipe("pizza", base, bonus, avaliable, QImage()));

    /*
     *
        Soup
        base: tomato sauce (is this considered tomatoes?), green chili, beet
        bonus: peppers, chiles, onion, or mushrooms
        fake: tuna, carrots, cabbage
     */
    base.push_back(ComparisonIngredient("green chili", false, true));
    base.push_back(ComparisonIngredient("tomato sauce", false, true));
    base.push_back(ComparisonIngredient("beet", true, true));
    base.push_back(ComparisonIngredient("chiles", false, true));
    bonus.push_back(ComparisonIngredient("peppers", true, true));
    bonus.push_back(ComparisonIngredient("mushrooms", true, true));
    bonus.push_back(ComparisonIngredient("onion", true, true));

    avaliable.push_back(Ingredient("green chili", QImage(folder + "Green Chili Pepper.png"),
                                   QImage(), QImage(), false, true, 0, 0));
    avaliable.push_back(Ingredient("tomato sauce", QImage(folder + "Tomato Sauce.png"),
                                   QImage(), QImage(), false, false, 0, 0));
    avaliable.push_back(Ingredient("beet", QImage(folder + "Red Beet.png"),
                                   QImage(), QImage(), false, false, 0, 0));
    avaliable.push_back(Ingredient("chiles", QImage(folder + "Red Chili Pepper.png"),
                                   QImage(), QImage(), true, true, 0, 0));
    // missing
    avaliable.push_back(Ingredient("peppers", QImage(folder + "Tomato.png"),
                                   QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("mushrooms", QImage(folder + "Mushroom.png"),
                                   QImage(folder + "Half Mushroom.png"), QImage(), true, true, 0, 0));
    avaliable.push_back(Ingredient("onion", QImage(folder + "Brown Onion.png"),
                                   QImage(folder + "Half brown onion"), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("carrots", QImage(folder + "Carrot.png"),
                                   QImage(folder + "Sliced Carrot.png"), QImage(), true, true, 0, 0));
    avaliable.push_back(Ingredient("tuna", QImage(folder + "Tuna.png"),
                                   QImage(folder + "Tuna Slice.png"), QImage(), true, false, 0, 0));
    // missing
    avaliable.push_back(Ingredient("cabbage", QImage(folder + "Cabbage.png"),
                                   QImage(), QImage(), true, false, 0, 0));
    recipes.push_back(Recipe("soup", base, bonus, avaliable, QImage()));

    /*
     * Hamburger
        base: Bun, patty, cheese, lettuce, tomato
        bonus: onion, ketchup, or avocado
        fake: cucumber, blueberry, chocolate, meatballs, cabbage, honey, tuna
    */
    base.push_back(ComparisonIngredient("bun", false, true));
    base.push_back(ComparisonIngredient("patty", false, true));
    base.push_back(ComparisonIngredient("cheese", true, true));
    base.push_back(ComparisonIngredient("lettuce", true, true));
    base.push_back(ComparisonIngredient("tomato", true, true));
    bonus.push_back(ComparisonIngredient("onion", true, true));
    bonus.push_back(ComparisonIngredient("ketchup", false, false));
    bonus.push_back(ComparisonIngredient("avocado", true, true));

    // missing
    avaliable.push_back(Ingredient("bun", QImage(folder + "Tomato.png"),
                                   QImage(), QImage(), false, true, 0, 0));
    // missing
    avaliable.push_back(Ingredient("patty", QImage(folder + "Raw Patty.png"),
                                   QImage(), QImage(), false, true, 0, 0));
    avaliable.push_back(Ingredient("cheese", QImage(folder + "Cheese Slice.png"),
                                   QImage(folder + "Cheddar"), QImage(), true, false, 0, 0));
    //missing
    avaliable.push_back(Ingredient("lettuce", QImage(folder + "Tomato.png"),
                                   QImage(), QImage(), false, false, 0, 0));
    avaliable.push_back(Ingredient("tomato", QImage(folder + "Tomato.png"),
                                   QImage(), QImage(), false, false, 0, 0));
    avaliable.push_back(Ingredient("onion", QImage(folder + "Brown Onion.png"),
                                   QImage(folder + "Half brown onion"), QImage(), true, false, 0, 0));
    //missing
    avaliable.push_back(Ingredient("ketchup", QImage(folder + "Tomato.png"),
                                   QImage(), QImage(), true, true, 0, 0));
    // missing
    avaliable.push_back(Ingredient("avocado", QImage(folder + "Tomato.png"),
                                   QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("cucumber", QImage(folder + "Cucumber.png"),
                                   QImage(folder + "Cucumber Slices.png"), QImage(), true, true, 0, 0));
    avaliable.push_back(Ingredient("blueberry", QImage(folder + "BlueBerry.png"),
                                   QImage(), QImage(), false, false, 0, 0));
    avaliable.push_back(Ingredient("chocolate", QImage(folder + "Milk Chocolate Bar.png"),
                                   QImage(), QImage(), true, false, 0, 0));
    // missing
    avaliable.push_back(Ingredient("cabbage", QImage(folder + "Cabbage.png"),
                                   QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("meatballs", QImage(folder + "Meatball.png"),
                                   QImage(), QImage(), false, true, 0, 0));
    avaliable.push_back(Ingredient("honey", QImage(folder + "Honey.png"),
                                   QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("tuna", QImage(folder + "Tuna.png"),
                                  QImage(folder + "Tuna Slice.png"), QImage(), true, false, 0, 0));
    recipes.push_back(Recipe("hamburger", base, bonus, avaliable, QImage("Hamburger Food.png")));

    /*
     *  Pancake
        base: milk, eggs, flour, sugar, bUtTeR
        bonus points: chocolate, syrup, strawberry
        fake: carrots, onion, cabbage, cucumber, meatballs, ketchup, tuna,
     */
    base.push_back(ComparisonIngredient("milk", false, true));
    base.push_back(ComparisonIngredient("eggs", false, true));
    base.push_back(ComparisonIngredient("flour", false, true));
    base.push_back(ComparisonIngredient("sugar", false, true));
    base.push_back(ComparisonIngredient("butter", false, true));
    bonus.push_back(ComparisonIngredient("chocolate", false, true));
    bonus.push_back(ComparisonIngredient("syrup", false, false));
    bonus.push_back(ComparisonIngredient("strawberry", false, false));

    avaliable.push_back(Ingredient("milk", QImage(folder + "Milk.png"),
                                   QImage(), QImage(), false, true, 0, 0));
    avaliable.push_back(Ingredient("eggs", QImage(folder + "Egg.png"),
                                   QImage(), QImage(folder + "Baked Egg.png"), false, false, 0, 0));
    avaliable.push_back(Ingredient("flour", QImage(folder + "Flour.png"),
                                   QImage(), QImage(), false, false, 0, 0));
    avaliable.push_back(Ingredient("sugar", QImage(folder + "Sugar.png"),
                                   QImage(), QImage(), false, false, 0, 0));
    avaliable.push_back(Ingredient("butter", QImage(folder + "Butter.png"),
                                   QImage(), QImage(), false, false, 0, 0));
    avaliable.push_back(Ingredient("chocolate", QImage(folder + "Milk Chocolate Bar.png"),
                                     QImage(), QImage(), true, false, 0, 0));
    // missing
    avaliable.push_back(Ingredient("syrup", QImage(folder + "Tomato.png"),
                                   QImage(), QImage(), true, true, 0, 0));
    avaliable.push_back(Ingredient("strawberry", QImage(folder + "Strawberry.png"),
                                   QImage(), QImage(), false, false, 0, 0));
    avaliable.push_back(Ingredient("carrots", QImage(folder + "Carrot.png"),
                                   QImage(folder + "Sliced Carrot.png"), QImage(), true, true, 0, 0));
    avaliable.push_back(Ingredient("onion", QImage(folder + "Brown Onion.png"),
                                   QImage(folder + "Half brown onion"), QImage(), true, false, 0, 0));
    // missing
    avaliable.push_back(Ingredient("cabbage", QImage(folder + "Cabbage.png"),
                                   QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("cucumber", QImage(folder + "Cucumber.png"),
                                   QImage(folder + "Cucumber Slices.png"), QImage(), true, true, 0, 0));
    avaliable.push_back(Ingredient("meatballs", QImage(folder + "Meatball.png"),
                                   QImage(), QImage(), false, true, 0, 0));
    // missing
    avaliable.push_back(Ingredient("ketchup", QImage(folder + "Tomato.png"),
                                   QImage(), QImage(), true, false, 0, 0));
    avaliable.push_back(Ingredient("tuna", QImage(folder + "Tuna.png"),
                                   QImage(folder + "Tuna Slice.png"), QImage(), true, false, 0, 0));
    recipes.push_back(Recipe("pancake", base, bonus, avaliable, QImage()));
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

void PlayerModel::calculateScore()
{
    int totalPoints = 100; // Score starts at 100

    Recipe recipe;
    for (const auto &rec : recipes) {
        if (QString::fromStdString(rec.getRecipeName()) == currentRecipe) {
            recipe = rec;
            break;
        }
    }

    // Checks for correct ingredient usage
    for (const auto &requiredIngredient : recipe.getBaseIngredients()) {
        bool found = false;

        for (const auto &usedIngredient : finalIngredients) {
            if (requiredIngredient.GetName() == usedIngredient.GetName()) {
                found = true;
                break;
            }
        }

        if (!found) {
            totalPoints -= 10; // Deducts points for missing ingredients
        }
    }

    // Checks for usage of bonus ingredients
    for (const auto &bonusIngredient : recipe.getBonusIngredients()) {
        for (const auto &usedIngredient : finalIngredients) {
            if (bonusIngredient.GetName() == usedIngredient.GetName()) {
                totalPoints += 10;
            }
        }
    }

    totalPoints = std::max(totalPoints, 0); // Prevents negative points

    finalScore = totalPoints;
}

int PlayerModel::getFinalScore() const
{
    return finalScore;
}
