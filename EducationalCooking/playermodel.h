/*
 * Name: everyone
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: Handles data and operations for most game logic. Includes,
 *      but is not limited to, setting up physics, data for recipes and
 *      scoring final dishes.
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

    explicit PlayerModel(Physics &physics, QObject *parent = nullptr);

    /// sets up our scene, using a recipe to spawn ingredients on a table
    /// and tools in their respective position, then starts the physics simulation.
    void setupScene();

    ///
    void setCurrentRecipe(const QString& recipe); // Used at startup

    ///
    const QString& getCurrentRecipe() const;

    ///
    Recipe& getSelectedRecipe();

    ///
    int getFinalScore() const;

    /// Returns a reference to the map of tool names to tool instances.
    std::map<std::string, Tool*>& getTools();

public slots:
    void handleRecipeClicked(const QString &recipeName);
    int calculateScore();
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
    void setupIngredientPhysics(Ingredient &ingredient);

    /// Spawns collision objects for the tools.
    void setupCookingToolPhysics(Tool tool);

    void setupRecipes();

    /// Creates instances of each tool we need for our kitchen
    /// and adds them to an easy-to-query map.
    void setupTools();

    /// Calls setupIngredientPhysics() for each ingredient in the recipe.
    void setupIngredients();

signals:
    void recipeClicked(const QString &recipeName);
    void selectedRecipeChanged(const QString &newRecipe);
};

#endif // PLAYERMODEL_H
