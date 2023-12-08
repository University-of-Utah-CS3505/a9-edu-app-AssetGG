#ifndef STARTUPSCREEN_H
#define STARTUPSCREEN_H

#include <QWidget>
#include "playermodel.h"
#include "playerview.h"
#include "recipecardwidget.h"

namespace Ui {
class StartupScreen;
}

class StartupScreen : public QWidget {
    Q_OBJECT

public:
    // Constructor
    StartupScreen(PlayerModel &model, PlayerView &view, QWidget *parent = nullptr);

    // Destructor
    ~StartupScreen();

private slots:
    // Slot for handling the click event on a recipe card
    void onRecipeCardClicked(int recipeIndex);

    // Slot for handling the click event on a specific recipe card
    void handleRecipeCardClicked(const QString &recipeName);

    // Slot for handling the click event on the "Learn Recipe" button
    void onLearnRecipeClicked();

private:
    // Vector to store recipe card widgets
    QVector<RecipeCardWidget*> recipeCards;

    // User interface object
    Ui::StartupScreen *ui;

    // Reference to the player model
    PlayerModel& playerModel;

    // Reference to the player view
    PlayerView &playerView;

    // Images for recipe cards
    QImage recipeCardImage1;
    QImage recipeCardImage2;
    QImage recipeCardImage3;
    QImage recipeCardImage4;
    QImage recipeCardImage5;
    QImage recipeCardImage6;

    // Method to create recipe card widgets
    void createRecipeCards();

    // Method to update a recipe card with a given recipe name
    void updateRecipeCard(RecipeCardWidget* card, const QString& recipeName);

    // Method to update the image of a recipe card with a given image path
    void updateRecipeCardImage(RecipeCardWidget* card, const QString& imagePath);
};

#endif // STARTUPSCREEN_H
