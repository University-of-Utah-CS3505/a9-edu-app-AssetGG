#include "playermodel.h"
#include "comparisoningredient.h"
#include "recipe.h"
#include "tools.h"

using std::map;
using std::vector;

PlayerModel::PlayerModel(Physics &physics, QObject *parent)
    : QObject{parent}
    , physics{physics}
{
    selectedRecipe = Recipe();
    currentlyClickedOn = nullptr;
    vector<Ingredient> base;
    finalScore = 0;
    setupRecipes();
}

// this method is when the learn recipe button is clicked in startupscreen
void PlayerModel::setupScene()
{
    setupWalls();
    setupTools();
    setupIngredients();
    physics.start();
}

void PlayerModel::setCurrentRecipe(const QString &recipe)
{
    currentRecipe = recipe;
    emit selectedRecipeChanged(currentRecipe); // May or may not be useful, as user cannot change recipe mid game
}

const QString &PlayerModel::getCurrentRecipe() const
{
    return currentRecipe;
}

Recipe &PlayerModel::getSelectedRecipe()
{
    return selectedRecipe;
}

int PlayerModel::getFinalScore() const
{
    return finalScore;
}

std::map<std::string, Tool *> &PlayerModel::getTools()
{
    return tools;
}

void PlayerModel::handleRecipeClicked(const QString &recipeName)
{
    qDebug() << "Recipe clicked:" << recipeName;
}

int PlayerModel::calculateScore()
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

                if (usedIngredient.IsCooked() != requiredIngredient.IsCooked()) {
                    totalPoints -= 10;
                }

                if (usedIngredient.IsCut() != requiredIngredient.IsCut()) {
                    totalPoints -= 10;
                }
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

    return finalScore;
}

vector<Ingredient> PlayerModel::getFinalIngredients()
{
    return finalIngredients;
}

void PlayerModel::addIngredientToFinalDish(Ingredient ingredientToAdd)
{
    if (std::find(finalIngredients.begin(), finalIngredients.end(), ingredientToAdd) == finalIngredients.end())
        finalIngredients.push_back(ingredientToAdd);
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

void PlayerModel::setupIngredientPhysics(Ingredient &ingredient)
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

void PlayerModel::setupCookingToolPhysics(Tool tool)
{
    // create a physics object for the tool
    QImage img = tool.GetImage();
    auto boxShape = Physics::createBoxShape(img.width() * 0.8, img.height() * 0.8);

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
#include "ingredient.h"


void PlayerModel::setupRecipes(){
    QString folder = ":/sprites/Sprites/";

    /*
     * Spaghetti
        base: noodles, sauce
        bonus: meatballs, chicken, cheese
        fake: milk, ketchup
    */

    vector<Ingredient> avaliableSpaghetti;
    vector<ComparisonIngredient> baseSpaghetti;
    vector<ComparisonIngredient> bonusSpaghetti;

    baseSpaghetti.push_back(ComparisonIngredient("spaghetti", false, true));
    baseSpaghetti.push_back(ComparisonIngredient("tomato sauce", false, false));
    bonusSpaghetti.push_back(ComparisonIngredient("meatballs", false, true));
    bonusSpaghetti.push_back(ComparisonIngredient("chicken", true, true));
    bonusSpaghetti.push_back(ComparisonIngredient("cheese", false, false));

    avaliableSpaghetti.push_back(Ingredient("noodles", QImage(folder + "Plain Pasta.png"),
                                            QImage(), QImage(folder + "Plain Pasta.png"), false, true, 550, 300));
    avaliableSpaghetti.push_back(Ingredient("tomato sauce", QImage(folder + "Tomato Sauce.png"),
                                            QImage(), QImage(), false, false, 550, 350));
    avaliableSpaghetti.push_back(Ingredient("meatballs", QImage(folder + "Meatball.png"),
                                            QImage(), QImage(folder + "Meatball.png"), false, true, 575, 350));
    avaliableSpaghetti.push_back(Ingredient("chicken", QImage(folder + "Raw Chicken.png"),
                                            QImage(folder + "Cut Chicken.png"), QImage(folder + "Cooked Chicken.png"), true, true, 575, 300));
    avaliableSpaghetti.push_back(Ingredient("cheese", QImage(folder + "Cheese Slice.png"),
                                            QImage(folder + "Cheddar"), QImage(), true, false, 600, 350));
    avaliableSpaghetti.push_back(Ingredient("milk", QImage(folder + "Milk.png"), QImage(), QImage(), false, false, 600, 300));
    avaliableSpaghetti.push_back(Ingredient("ketchup", QImage(folder + "Ketchup.png"), QImage(), QImage(), false, false, 575, 400));
    recipes.push_back(Recipe("Spaghetti", baseSpaghetti, bonusSpaghetti, avaliableSpaghetti));

    /*
     * Salad
        base: lettuce, salad dressing
        bonus: cheese, tomato, cucumber
        fake: sugar, ketchup
     */

    vector<Ingredient> avaliableSalad;
    vector<ComparisonIngredient> baseSalad;
    vector<ComparisonIngredient> bonusSalad;

    baseSalad.push_back(ComparisonIngredient("lettuce", true, false));
    baseSalad.push_back(ComparisonIngredient("salad dressing", false, false));
    bonusSalad.push_back(ComparisonIngredient("tomato", true, false));
    bonusSalad.push_back(ComparisonIngredient("cucumber", true, false));
    bonusSalad.push_back(ComparisonIngredient("cheese", false, false));


    avaliableSalad.push_back(Ingredient("lettuce", QImage(folder + "Lettuce.png"),
                                        QImage(folder + "Chopped Lettuce.png"), QImage(), true, false, 550, 300));
    avaliableSalad.push_back(Ingredient("salad dressing", QImage(folder + "Salad Dressing.png"),
                                        QImage(), QImage(), false, false, 575, 300));
    avaliableSalad.push_back(Ingredient("tomato", QImage(folder + "Tomato.png"),
                                        QImage(folder + "Cut Tomato.png"), QImage(), true, false, 550, 350));
    avaliableSalad.push_back(Ingredient("cucumber", QImage(folder + "Cucumber.png"),
                                        QImage(folder + "Cucumber Slices.png"), QImage(), true, false, 575, 350));
    avaliableSalad.push_back(Ingredient("cheese", QImage(folder + "Cheese Slice.png"),
                                        QImage(folder + "Cheddar"), QImage(), true, false, 600, 300));
    avaliableSalad.push_back(Ingredient("sugar", QImage(folder + "sugar.png"),
                                        QImage(), QImage(), false, false, 600, 350));
    avaliableSalad.push_back(Ingredient("ketchup", QImage(folder + "Ketchup.png"),
                                        QImage(), QImage(), false, false, 575, 400));
    recipes.push_back(Recipe("Salad", baseSalad, bonusSalad, avaliableSalad));

    /*
     * Pizza
        base: dough, cheese, sausage, tomato sauce
        bonus: peppers, chiles, or onion
        fake: carrots, honey, ketchup
     */

    vector<Ingredient> avaliablePizza;
    vector<ComparisonIngredient> basePizza;
    vector<ComparisonIngredient> bonusPizza;

    basePizza.push_back(ComparisonIngredient("dough", false, true));
    basePizza.push_back(ComparisonIngredient("tomato sauce", false, true));
    basePizza.push_back(ComparisonIngredient("cheese", false, true));
    basePizza.push_back(ComparisonIngredient("sausage", true, true));
    bonusPizza.push_back(ComparisonIngredient("peppers", true, true));
    bonusPizza.push_back(ComparisonIngredient("chiles", true, true));
    bonusPizza.push_back(ComparisonIngredient("onion", true, true));

    avaliablePizza.push_back(Ingredient("dough", QImage(folder + "Dough.png"),
                                        QImage(), QImage(folder + "Pita Bread.png"), false, true, 550, 300));
    avaliablePizza.push_back(Ingredient("tomato sauce", QImage(folder + "Tomato Sauce.png"),
                                        QImage(), QImage(), false, false, 575, 350));
    avaliablePizza.push_back(Ingredient("cheese", QImage(folder + "Cheese Slice.png"),
                                        QImage(folder + "Cheddar"), QImage(), true, false, 575, 300));
    avaliablePizza.push_back(Ingredient("sausage", QImage(folder + "Raw Sausage.png"),
                                        QImage(folder + "Half Pepperoni.png"),
                                        QImage(folder + "Cooked Sausage.png"), true, true, 550, 350));
    avaliablePizza.push_back(Ingredient("bell peppers", QImage(folder + "bell_pepper.png"),
                                        QImage(folder + "Cut Bell Pepper.png"), QImage(), true, false, 600, 250));
    avaliablePizza.push_back(Ingredient("chiles", QImage(folder + "Green Chili Pepper.png"),
                                        QImage(folder + "Cut Green Chillis"), QImage(), true, false, 600, 350));
    avaliablePizza.push_back(Ingredient("onion", QImage(folder + "Brown Onion.png"),
                                        QImage(folder + "Half brown onion"), QImage(), true, false, 550, 250));
    avaliablePizza.push_back(Ingredient("carrots", QImage(folder + "Carrot.png"),
                                        QImage(folder + "Sliced Carrot.png"), QImage(), true, false, 575, 250));
    avaliablePizza.push_back(Ingredient("honey", QImage(folder + "Honey.png"),
                                        QImage(), QImage(), false, false, 600, 300));
    avaliablePizza.push_back(Ingredient("ketchup", QImage(folder + "Ketchup.png"),
                                        QImage(), QImage(), false, false, 575, 400));
    recipes.push_back(Recipe("Pepperoni Pizza", basePizza, bonusPizza, avaliablePizza));

    /*
     *
        Soup
        base: tomato sauce (is this considered tomatoes?), green chili, beet
        bonus: peppers, chiles, onion, or mushrooms
        fake: tuna, carrots, cabbage
     */

    vector<Ingredient> avaliableSoup;
    vector<ComparisonIngredient> baseSoup;
    vector<ComparisonIngredient> bonusSoup;

    baseSoup.push_back(ComparisonIngredient("green chili", false, true));
    baseSoup.push_back(ComparisonIngredient("tomato sauce", false, true));
    baseSoup.push_back(ComparisonIngredient("beet", true, true));
    baseSoup.push_back(ComparisonIngredient("chiles", false, true));
    bonusSoup.push_back(ComparisonIngredient("peppers", true, true));
    bonusSoup.push_back(ComparisonIngredient("mushrooms", true, true));
    bonusSoup.push_back(ComparisonIngredient("onion", true, true));

    avaliableSoup.push_back(Ingredient("green chili", QImage(folder + "Green Chili Pepper.png"),
                                       QImage(folder + "Cut Green Chillis.png"), QImage(), true, false, 550, 300));
    avaliableSoup.push_back(Ingredient("tomato sauce", QImage(folder + "Tomato Sauce.png"),
                                       QImage(), QImage(), false, false, 575, 350));
    avaliableSoup.push_back(Ingredient("beet", QImage(folder + "Red Beet.png"),
                                       QImage(folder + "Cut Radish.png"), QImage(), true, false, 600, 400));
    avaliableSoup.push_back(Ingredient("chiles", QImage(folder + "Red Chili Pepper.png"),
                                       QImage(), QImage(), false, false, 550, 350));
    avaliableSoup.push_back(Ingredient("peppers", QImage(folder + "bell_pepper.png"),
                                       QImage(folder + "Cut Bell Pepper.png"), QImage(), true, false, 575, 400));
    avaliableSoup.push_back(Ingredient("mushrooms", QImage(folder + "Mushroom.png"),
                                       QImage(folder + "Half Mushroom.png"), QImage(), true, false, 600, 300));
    avaliableSoup.push_back(Ingredient("onion", QImage(folder + "Brown Onion.png"),
                                       QImage(folder + "Half brown onion"), QImage(), true, false, 550, 400));
    avaliableSoup.push_back(Ingredient("carrots", QImage(folder + "Carrot.png"),
                                       QImage(folder + "Sliced Carrot.png"), QImage(), true, false, 575, 300));
    avaliableSoup.push_back(Ingredient("tuna", QImage(folder + "Tuna.png"),
                                       QImage(folder + "Tuna Slice.png"), QImage(), true, false, 600, 350));
    avaliableSoup.push_back(Ingredient("cabbage", QImage(folder + "Cabbage.png"),
                                       QImage(folder + "Chopped Cabbage.png"), QImage(), true, false, 575, 250));
    recipes.push_back(Recipe("Soup", baseSoup, bonusSoup, avaliableSoup));

    /*
     * Hamburger
        base: Bun, patty, cheese, lettuce, tomato
        bonus: onion, ketchup, or avocado
        fake: cucumber, blueberry, chocolate, meatballs, cabbage, honey, tuna
    */

    vector<Ingredient> avaliableHamburger;
    vector<ComparisonIngredient> baseHamburger;
    vector<ComparisonIngredient> bonusHamburger;

    baseHamburger.push_back(ComparisonIngredient("bun", false, true));
    baseHamburger.push_back(ComparisonIngredient("patty", false, true));
    baseHamburger.push_back(ComparisonIngredient("cheese", true, true));
    baseHamburger.push_back(ComparisonIngredient("lettuce", true, true));
    baseHamburger.push_back(ComparisonIngredient("tomato", true, true));
    bonusHamburger.push_back(ComparisonIngredient("onion", true, true));
    bonusHamburger.push_back(ComparisonIngredient("ketchup", false, false));
    bonusHamburger.push_back(ComparisonIngredient("avocado", true, true));


    avaliableHamburger.push_back(Ingredient("bun", QImage(folder + "Bun.png"),
                                            QImage(), QImage(folder + "Bun.png"), false, true, 550, 250));
    avaliableHamburger.push_back(Ingredient("patty", QImage(folder + "Raw Patty.png"),
                                            QImage(), QImage(folder + "Cooked Patty.png"), false, true, 550, 200));
    avaliableHamburger.push_back(Ingredient("cheese", QImage(folder + "Cheese Slice.png"),
                                            QImage(folder + "Cheddar"), QImage(), true, false, 550, 300));
    avaliableHamburger.push_back(Ingredient("lettuce", QImage(folder + "Lettuce.png"),
                                            QImage(folder + "Chopped Lettuce.png"), QImage(), true, false, 550, 350));
    avaliableHamburger.push_back(Ingredient("tomato", QImage(folder + "Tomato.png"),
                                            QImage(folder + "Cut Tomato.png"), QImage(), true, false, 550, 400));
    avaliableHamburger.push_back(Ingredient("onion", QImage(folder + "Brown Onion.png"),
                                            QImage(folder + "Half brown onion"), QImage(), true, false, 575, 200));
    avaliableHamburger.push_back(Ingredient("ketchup", QImage(folder + "Ketchup.png"),
                                            QImage(), QImage(), false, false, 575, 300));
    avaliableHamburger.push_back(Ingredient("avocado", QImage(folder + "Avocado.png"),
                                            QImage(folder + "Half Avocado.png"), QImage(), true, false, 575, 400));
    avaliableHamburger.push_back(Ingredient("cucumber", QImage(folder + "Cucumber.png"),
                                            QImage(folder + "Cucumber Slices.png"), QImage(), true, false, 575, 350));
    avaliableHamburger.push_back(Ingredient("blueberry", QImage(folder + "Blueberry.png"),
                                            QImage(), QImage(), false, false, 575, 250));
    avaliableHamburger.push_back(Ingredient("chocolate", QImage(folder + "Milk Chocolate Bar.png"),
                                            QImage(), QImage(), false, false, 600, 200));
    avaliableHamburger.push_back(Ingredient("cabbage", QImage(folder + "Cabbage.png"),
                                            QImage(folder + "Chopped Cabbage.png"), QImage(), true, false, 600, 250));
    avaliableHamburger.push_back(Ingredient("meatballs", QImage(folder + "Meatball.png"),
                                            QImage(), QImage(folder + "Meatball.png"), false, true, 600, 300));
    avaliableHamburger.push_back(Ingredient("honey", QImage(folder + "Honey.png"),
                                            QImage(), QImage(), false, false, 600, 350));
    avaliableHamburger.push_back(Ingredient("tuna", QImage(folder + "Tuna.png"),
                                            QImage(folder + "Tuna Slice.png"), QImage(), true, false, 600, 400));
    recipes.push_back(Recipe("Hamburger", baseHamburger, bonusHamburger, avaliableHamburger));

    /*
     *  Pancake
        base: milk, eggs, flour, sugar, bUtTeR
        bonus points: chocolate, syrup, strawberry
        fake: carrots, onion, cabbage, cucumber, meatballs, ketchup, tuna,
     */

    vector<Ingredient> avaliablePancake;
    vector<ComparisonIngredient> basePancake;
    vector<ComparisonIngredient> bonusPancake;

    basePancake.push_back(ComparisonIngredient("milk", false, true));
    basePancake.push_back(ComparisonIngredient("eggs", false, true));
    basePancake.push_back(ComparisonIngredient("flour", false, true));
    basePancake.push_back(ComparisonIngredient("sugar", false, true));
    basePancake.push_back(ComparisonIngredient("butter", false, true));
    bonusPancake.push_back(ComparisonIngredient("chocolate", false, true));
    bonusPancake.push_back(ComparisonIngredient("syrup", false, false));
    bonusPancake.push_back(ComparisonIngredient("strawberry", false, false));

    avaliablePancake.push_back(Ingredient("milk", QImage(folder + "Milk.png"),
                                          QImage(), QImage(), false, false, 550, 200));
    avaliablePancake.push_back(Ingredient("eggs", QImage(folder + "Egg.png"),
                                          QImage(), QImage(folder + "Baked Egg.png"), false, true, 550, 250));
    avaliablePancake.push_back(Ingredient("flour", QImage(folder + "Flour.png"),
                                          QImage(), QImage(), false, false, 550, 300));
    avaliablePancake.push_back(Ingredient("sugar", QImage(folder + "sugar.png"),
                                          QImage(), QImage(), false, false, 550, 400));
    avaliablePancake.push_back(Ingredient("butter", QImage(folder + "Butter.png"),
                                          QImage(), QImage(), false, false, 550, 350));
    avaliablePancake.push_back(Ingredient("chocolate", QImage(folder + "Milk Chocolate Bar.png"),
                                          QImage(), QImage(), false, false, 575, 200));
    avaliablePancake.push_back(Ingredient("syrup", QImage(folder + "Syrup.png"),
                                          QImage(), QImage(), false, false, 575, 250));
    avaliablePancake.push_back(Ingredient("strawberry", QImage(folder + "Strawberry.png"),
                                          QImage(), QImage(), false, false, 575, 300));
    avaliablePancake.push_back(Ingredient("carrots", QImage(folder + "Carrot.png"),
                                          QImage(folder + "Sliced Carrot.png"), QImage(), true, false, 575, 350));
    avaliablePancake.push_back(Ingredient("onion", QImage(folder + "Brown Onion.png"),
                                          QImage(folder + "Half brown onion"), QImage(), true, false, 575, 400));
    avaliablePancake.push_back(Ingredient("cabbage", QImage(folder + "Cabbage.png"),
                                          QImage(folder + "Chopped Cabbage.png"), QImage(), true, false, 600, 200));
    avaliablePancake.push_back(Ingredient("cucumber", QImage(folder + "Cucumber.png"),
                                          QImage(folder + "Cucumber Slices.png"), QImage(), true, false, 600, 250));
    avaliablePancake.push_back(Ingredient("meatballs", QImage(folder + "Meatball.png"),
                                          QImage(), QImage(), false, false, 600, 300));
    avaliablePancake.push_back(Ingredient("ketchup", QImage(folder + "Ketchup.png"),
                                          QImage(), QImage(), false, false, 600, 350));
    avaliablePancake.push_back(Ingredient("tuna", QImage(folder + "Tuna.png"),
                                          QImage(folder + "Tuna Slice.png"), QImage(), true, false, 600, 400));
    recipes.push_back(Recipe("Pancake", basePancake, bonusPancake, avaliablePancake));
}

void PlayerModel::setupTools()
{
    // polymorphism in cpp is braindead, so we're forced to
    // make our tools map a map of pointers to the Base type.
    // Only way to get a pointer a Tool with a lifetime longer than
    // The scope of this method is to allocate on the heap.
    tools.insert({"CuttingBoard", new CuttingBoard(230, 410)});
    tools.insert({"FryingPan", new FryingPan(282, 90)});
    tools.insert({"Pot", new Pot(405, 75)});
    for (auto &[toolName, tool] : tools) {
        setupCookingToolPhysics(*tool);
    }
}

void PlayerModel::setupIngredients()
{
    for (Recipe &r : recipes) {
        if (currentRecipe.toStdString() == r.getRecipeName()) {
            selectedRecipe = r;
            break;
        }
    }
    for (Ingredient &ingredient : selectedRecipe.getAvaliableIngredients()) {
        setupIngredientPhysics(ingredient);
    }
}
