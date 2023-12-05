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

    // sets up our scene, using a recipe to spawn ingredients on a table
    void setupScene();
    void setCurrentRecipe(const QString& recipe); // Used at startup
    const QString& getCurrentRecipe() const;
    Recipe& getSelectedRecipe();

    int getFinalScore() const;
    std::map<std::string, Tool*>& getTools();
    Ingredient *getIngredientFromName(std::string ingredientName);

public slots:
    void handleRecipeClicked(const QString &recipeName);
    int calculateScore();
    vector<Ingredient> getFinalIngredients();
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

    void setupWalls();
    void setupIngredientPhysics(Ingredient &ingredient);
    void setupCookingToolPhysics(Tool tool);
    void setupRecipes();
    void setupTools();
    void setupIngredients();

signals:
    void recipeClicked(const QString &recipeName);
    void updateIngredientOnScreen(QImage*, int, int);
    void selectedRecipeChanged(const QString &newRecipe);

};

#endif // PLAYERMODEL_H
