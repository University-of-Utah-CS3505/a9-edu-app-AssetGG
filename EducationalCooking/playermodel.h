#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <QObject>
#include <QPoint>
#include <QImage>
#include "ingredient.h"
#include "physics.h"
#include "recipe.h"

using std::vector;

class PlayerModel : public QObject
{
    Q_OBJECT
public:
    Physics &physics;

    explicit PlayerModel(Physics &physics, QObject *parent = nullptr);

    // sets up our scene, using a recipe to spawn ingredients on a table
    void setupScene(Recipe &recipe);

    void setCurrentRecipe(const QString& recipe); // Used at startup

    const QString& getCurrentRecipe() const;

public slots:
    void handleRecipeClicked(const QString &recipeName);

private:
    vector<Recipe> recipes;
    vector<Ingredient> ingredients;
    QString currentRecipe;
    Ingredient *currentlyClickedOn;

    void setupWalls();
    void setupIngredient(Ingredient &ingredient);

signals:
    void recipeClicked(const QString &recipeName);
    void updateIngredientOnScreen(QImage*, int, int);
    void selectedRecipeChanged(const QString &newRecipe);

};

#endif // PLAYERMODEL_H
