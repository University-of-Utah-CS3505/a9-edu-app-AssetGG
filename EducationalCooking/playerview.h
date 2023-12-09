/*
 * Name: Everyone
 * Reviewed By: Nathaniel Taylor
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: Sets up the data and operations for UI components of the game.
 * Including, but not limited to, user input events, scene drawing,
 * and the recipe help button.
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
namespace Ui
{
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

    /// Sets up the recipe help feature and adds all of the ingredient sprites needed for the chosen recipe to the view
    void setupScene(Recipe &recipe, std::map<std::string, Tool*> &tools);

    /// Updates a sprites position based on whether it is an ingredient or cooking tool
    void updateSpritePositions(const std::map<std::string, Physics::PhysicsObject>&);

    /// Fire's signals to determine the user's final score and their final dish and sets up the user's end game screen
    void onScoreButtonClicked();

    /// Returns a pointer to the view Ingredient if it exists, or
    /// a nullptr if it doesn't.
    Ingredient *getIngredientByName(std::string);

public slots:

    ///Repaints all sprites and kitchen tools at their positions
    /// (positions only update if the user clicks on them and drags them around)
    void paintEvent(QPaintEvent *);

    ///Updates the position of the sprite clicked on
    void mouseMoveEvent(QMouseEvent *);

    ///Determines if the mouse press happened on an ingredient or a cooking tool
    void mousePressEvent(QMouseEvent *);

    ///Tells the model no ingredient or cooking tool is clicked on anymore
    void mouseReleaseEvent(QMouseEvent *);

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
    void setupRecipeHelpLine3(Recipe);

    ///Sets up the fourth line of the recipe help feature
    void setupRecipeHelpLine4(Recipe);

    /// Returns a pointer to the view Tool if it exists,
    /// or a nullptr if it doesn't.
    Tool *getToolByName(std::string);

signals:

    /// Fire's whenever the user presses their mouse while hovering over
    /// an item
    void itemGrabbed(std::string, bool, QPoint);

    /// Fire's when the user, who is dragging an ingredient, releases their
    /// mouse button.
    void itemDropped(QPoint);

    /// Fire's each time the user's mouse position updates while dragging.
    void updateDragPosition(QPoint);

    /// Retrieves the user's final score from the model
    int calculateScoreRequested();

    /// Retrieves the vector of ingredients the user has
    /// put into their final dish from the model
    vector<Ingredient> getFinalIngredientsRequested();

    ///Tells the model to add an ingredient to the final dish
    void addItemToFinalDishIngredients(Ingredient);
};
#endif // PLAYERVIEW_H
