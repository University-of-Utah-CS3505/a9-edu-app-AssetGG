#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <QObject>
#include <QPoint>
#include <QImage>
#include "ingredient.h"
#include "recipe.h"

using std::vector;

class PlayerModel : public QObject
{
    Q_OBJECT
public:
    explicit PlayerModel(QObject *parent = nullptr);

    void setCurrentRecipe(const QString& recipe); // Used at startup

    const QString& getCurrentRecipe() const;

public slots:
    void handleRecipeClicked(const QString &recipeName);

private:
    vector<Recipe> recipes;
    vector<Ingredient> ingredients;
    Ingredient* currentlyClickedOn;
    QString currentRecipe;

signals:
    void recipeClicked(const QString &recipeName);
    void updateIngredientOnScreen(QImage*, int, int);
    void selectedRecipeChanged(const QString &newRecipe);

};

#endif // PLAYERMODEL_H
