#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <QObject>
#include <QPoint>
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

public slots:

private:
    vector<Recipe> recipes;
    vector<Ingredient> ingredients;
    Ingredient *currentlyClickedOn;

    void setupWalls();
    void setupIngredient(Ingredient &ingredient);

signals:
    void updateIngredientOnScreen(QImage*, int, int);

};

#endif // PLAYERMODEL_H
