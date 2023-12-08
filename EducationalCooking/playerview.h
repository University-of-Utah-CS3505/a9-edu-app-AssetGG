/*
 * Name: everyone
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: Handles data and operations for UI components of the game.
 *      Includes, but is not limited to, user input events, scene drawing,
 *      and the recipe help button.
 */

#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <QLabel>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QTimer>
#include "ingredient.h"
#include "physics.h"
#include "recipe.h"
#include "tools.h"

using std::vector;

QT_BEGIN_NAMESPACE
namespace Ui {
class PlayerView;
}
QT_END_NAMESPACE

class PlayerView : public QMainWindow
{
    Q_OBJECT
    std::map<std::string, Tool *> *tools;
    std::map<std::string, Ingredient> ingredientSprites;

public:
    PlayerView(QWidget *parent = nullptr);
    ~PlayerView();
    void setupScene(Recipe &recipe, std::map<std::string, Tool *> &tools);
    void updateSpritePositions(const std::map<std::string, Physics::PhysicsObject> &physicsObjects);
    void onScoreButtonClicked();

    /// Returns a pointer to the view Ingredient if it exists, or
    /// a nullptr if it doesn't.
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

    ///Sets up the first line of the recipe help feature
    void setupRecipeHelpLine1(Recipe);

    ///Sets up the second line of the recipe help feature
    void setupRecipeHelpLine2(Recipe);

    ///Sets up the third line of the recipe help feature
    void setupRecipeHelpLine3();

    ///Sets up the fourth line of the recipe help feature
    void setupRecipeHelpLine4(Recipe);

    /// Returns a pointer to the view Tool if it exists,
    /// or a nullptr if it doesn't.
    Tool *getToolByName(std::string name);

signals:
    /// Fire's whenever the user presses their mouse while hovering over
    /// an item
    void itemGrabbed(std::string itemName, bool isIngredient, QPoint mousePos);

    /// Fire's when the user, who is dragging an ingredient, releases their
    /// mouse button.
    void itemDropped(QPoint mousePos);

    /// Fire's each time the user's mouse position updates while dragging.
    void updateDragPosition(QPoint mousePos);

    ///
    int calculateScoreRequested();

    ///
    vector<Ingredient> getFinalIngredientsRequested();

    ///Tells the model to add an ingredient to the final dish
    void addItemToFinalDishIngredients(Ingredient);
};
#endif // PLAYERVIEW_H
