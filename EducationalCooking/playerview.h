#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QLabel>
#include "ingredient.h"
#include "physics.h"
#include "recipe.h"
#include "tools.h"
#include <map>

using std::vector;

QT_BEGIN_NAMESPACE
namespace Ui {
class PlayerView;
}
QT_END_NAMESPACE

class PlayerView : public QMainWindow
{
    Q_OBJECT
    std::map<std::string, Tool*> *tools;
    std::map<std::string, Ingredient> ingredientSprites;

public:
    PlayerView(QWidget *parent = nullptr);
    ~PlayerView();
    void setupScene(Recipe &recipe, std::map<std::string, Tool*> &tools);
    void updateSpritePositions(const std::map<std::string, Physics::PhysicsObject> &physicsObjects);
    void onScoreButtonClicked();

    Ingredient *getIngredientByName(std::string name);

public slots:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::PlayerView *ui;
    QLabel *recipeHelpLine1;
    QLabel *recipeHelpLine2;
    QLabel *recipeHelpLine3;
    QLabel *recipeHelpLine4;
    bool showRecipeHelp;
    Recipe chosenRecipe;
    Ingredient clickedIngredient;

    Ingredient *getSpriteByName(std::string name);
    void setupRecipeHelpLine1(Recipe);
    void setupRecipeHelpLine2(Recipe);
    void setupRecipeHelpLine3(Recipe);
    void setupRecipeHelpLine4(Recipe);
    Tool *getToolByName(std::string name);
    int calculateScore();

signals:
    void itemGrabbed(std::string itemName, bool isIngredient, QPoint mousePos);
    void itemDropped(QPoint mousePos);
    void updateDragPosition(QPoint mousePos);
    int calculateScoreRequested();
    vector<Ingredient> getFinalIngredientsRequested();
    void removeItemFromIngredientsInWorld(Ingredient);
    void addItemToFinalDishIngredients(Ingredient);
};
#endif // PLAYERVIEW_H
