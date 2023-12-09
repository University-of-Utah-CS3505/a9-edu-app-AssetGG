/*
 * Name: Everyone
 * Reviewed By: Nathaniel Taylor
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: Sets up the data and operations for most game logic. Including,
 * but not limited to, setting up physics, data for recipes and
 * scoring final dishes.
 */

#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <QImage>
#include <QObject>
#include <QPoint>
#include "ingredient.h"
#include "physics.h"
#include "recipe.h"
#include "tools.h"
#include <map>

using std::vector;

class PlayerModel : public QObject
{
    Q_OBJECT
public:
    Physics &physics;

    explicit PlayerModel(Physics&, QObject *parent = nullptr);

    /// Sets up our scene, using a recipe to spawn ingredients on a table
    /// and tools in their respective position, then starts the physics simulation.
    void setupScene();

    /// Used to tell the model what recipe the user chose
    void setCurrentRecipe(const QString&); // Used at startup

    /// Getter method for current recipe name
    const QString& getCurrentRecipe() const;

    /// Getter method for recipe object
    Recipe& getSelectedRecipe();

    /// Retrieves the user's final score
    int getFinalScore() const;

    /// Returns a reference to the map of tool names to tool instances.
    std::map<std::string, Tool*>& getTools();

public slots:

    /// Calculates the user's final score by looking at what ingredients they have in their final dish
    int calculateScore();

    /// A getter method that retrieves a vector containing all of the ingredients the user has in their final dish
    vector<Ingredient> getFinalIngredients();

    /// Adds the given ingredient to the vector of finalIngredient.
    /// All ingredients in this vector will be counted towards their final score.
    void addIngredientToFinalDish(Ingredient);

private:
    vector<Recipe> recipes;
    vector<Ingredient> ingredients;
    vector<Ingredient> finalIngredients;
    QString currentRecipe;
    Ingredient *currentlyClickedOn;
    int finalScore;
    Recipe selectedRecipe;
    std::map<std::string, Tool*> tools;

    /// Spawns static collision objects for the walls
    void setupWalls();

    /// Spawns dynamic collision objects for the ingredients
    void setupIngredientPhysics(Ingredient&);

    /// Spawns collision objects for the tools.
    void setupCookingToolPhysics(Tool);

    /// Creates all recipes and fills the recipe vector
    void setupRecipes();

    /// Creates instances of each tool we need for our kitchen
    /// and adds them to an easy-to-query map.
    void setupTools();

    /// Calls setupIngredientPhysics() for each ingredient in the recipe.
    void setupIngredients();
};

#endif // PLAYERMODEL_H
