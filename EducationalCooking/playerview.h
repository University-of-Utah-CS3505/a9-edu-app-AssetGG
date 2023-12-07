#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QLabel>
#include <QTimer>
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

    ///Repaints all sprites and kitchen tools at their positions
    /// (positions only update if the user clicks on them and drags them around)
    void paintEvent(QPaintEvent *event);

    ///Updates the position of the sprite clicked on
    void mouseMoveEvent(QMouseEvent *event);

    ///Determines if the mouse press happened on an ingredient or a cooking tool
    void mousePressEvent(QMouseEvent *event);

    ///Tells the model no ingredient or cooking tool is clicked on anymore
    void mouseReleaseEvent(QMouseEvent *event);

private slots:

    ///Hides the label that tells the user what was added to the final dish
    void hideIngredientAdded();

private:
    Ui::PlayerView *ui;
    QLabel *recipeHelpLine1;
    QLabel *recipeHelpLine2;
    QLabel *recipeHelpLine3;
    QLabel *recipeHelpLine4;
    QLabel *addedSomethingToDishLabel;
    QImage finalDishBowl;
    QTimer hideLabelTimer;
    bool showRecipeHelp;
    Recipe chosenRecipe;
    Ingredient clickedIngredient;

    Ingredient *getSpriteByName(std::string name);

    ///Sets up the first line of the recipe help feature
    void setupRecipeHelpLine1(Recipe);

    ///Sets up the second line of the recipe help feature
    void setupRecipeHelpLine2(Recipe);

    ///Sets up the third line of the recipe help feature
    void setupRecipeHelpLine3(Recipe);

    ///Sets up the fourth line of the recipe help feature
    void setupRecipeHelpLine4(Recipe);
    Tool *getToolByName(std::string name);
    int calculateScore();

signals:
    void itemGrabbed(std::string itemName, bool isIngredient, QPoint mousePos);
    void itemDropped(QPoint mousePos);
    void updateDragPosition(QPoint mousePos);
    int calculateScoreRequested();
    vector<Ingredient> getFinalIngredientsRequested();

    ///Tells the model to add an ingredient to the final dish
    void addItemToFinalDishIngredients(Ingredient);
};
#endif // PLAYERVIEW_H
