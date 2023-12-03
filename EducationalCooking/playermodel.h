#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <QImage>
#include <QObject>
#include <QPoint>
#include "ingredient.h"
#include "physics.h"
#include "recipe.h"
#include "tools.h"
#include "comparisoningredient.h"

using std::vector;

class PlayerModel : public QObject
{
    Q_OBJECT
public:
    Physics &physics;

    explicit PlayerModel(Physics &physics, QObject *parent = nullptr);

    // sets up our scene, using a recipe to spawn ingredients on a table
    void setupScene(Recipe &recipe, std::map<std::string, Tool> &tools);
    void setCurrentRecipe(const QString& recipe); // Used at startup
    const QString& getCurrentRecipe() const;

    int getFinalScore() const;

public slots:
    void handleRecipeClicked(const QString &recipeName);
    void calculateScore();

private:
    vector<Recipe> recipes;
    vector<Ingredient> ingredients;
    vector<Ingredient> finalIngredients;
    QString currentRecipe;
    Ingredient *currentlyClickedOn;
    int finalScore;

    void setupWalls();
    void setupIngredient(Ingredient &ingredient);
    void setupCookingTool(Tool tool);
    void setupRecipes();

signals:
    void recipeClicked(const QString &recipeName);
    void updateIngredientOnScreen(QImage*, int, int);
    void selectedRecipeChanged(const QString &newRecipe);

};

#endif // PLAYERMODEL_H
