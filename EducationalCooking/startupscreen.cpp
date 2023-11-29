#include "ui_startupscreen.h"
#include "startupscreen.h"
#include "recipecardwidget.h"
#include "playerview.h"

StartupScreen::StartupScreen(PlayerModel& model, QWidget *parent)
    : QWidget(parent), ui(new Ui::StartupScreen), playerModel(model) {
    ui->setupUi(this);

    connect(ui->recipeCard1, &RecipeCardWidget::clicked, this, [this]() { onRecipeCardClicked(0); });
    connect(ui->recipeCard2, &RecipeCardWidget::clicked, this, [this]() { onRecipeCardClicked(1); });
    connect(ui->recipeCard3, &RecipeCardWidget::clicked, this, [this]() { onRecipeCardClicked(2); });
    connect(ui->recipeCard4, &RecipeCardWidget::clicked, this, [this]() { onRecipeCardClicked(3); });
    connect(ui->recipeCard5, &RecipeCardWidget::clicked, this, [this]() { onRecipeCardClicked(4); });
    connect(ui->recipeCard6, &RecipeCardWidget::clicked, this, [this]() { onRecipeCardClicked(5); });

    connect(ui->learnRecipeButton, &QPushButton::clicked, this, &StartupScreen::onLearnRecipeClicked);

    createRecipeCards();
}

StartupScreen::~StartupScreen() {
    delete ui;
}

void StartupScreen::onRecipeCardClicked(int recipeIndex) {
    //Todo: update selected recipe
}

void StartupScreen::onLearnRecipeClicked() {
    PlayerView* playerView = new PlayerView;
    playerView->show(); // Shows playerView after recipe is selected

    this->hide();
}

void StartupScreen::createRecipeCards() {
    recipeCardImage1 = QImage(":/sprites/Sprites/Pasta Tomato.png");
    recipeCardImage2 = QImage(":/sprites/Sprites/Salad Dish.png");
    recipeCardImage3 = QImage(":/sprites/Sprites/Cheese Pasta.png");
    recipeCardImage4 = QImage(":/sprites/Sprites/Chicken Soup.png");
    recipeCardImage5 = QImage(":/sprites/Sprites/Cheeseburger.png");
    recipeCardImage6 = QImage(":/sprites/Sprites/Pancakes.png");

    updateRecipeCard(ui->recipeCard1, "Spaghetti");
    updateRecipeCard(ui->recipeCard2, "Salad");
    updateRecipeCard(ui->recipeCard3, "Pizza");
    updateRecipeCard(ui->recipeCard4, "Soup");
    updateRecipeCard(ui->recipeCard5, "Hamburger");
    updateRecipeCard(ui->recipeCard6, "Pancake");

    // Update recipe images
    updateRecipeCardImage(ui->recipeCard1, ":/sprites/Sprites/Pasta Tomato.png");
    updateRecipeCardImage(ui->recipeCard2, ":/sprites/Sprites/Salad Dish.png");
    updateRecipeCardImage(ui->recipeCard3, ":/sprites/Sprites/Cheese Pasta.png");
    updateRecipeCardImage(ui->recipeCard4, ":/sprites/Sprites/Chicken Soup.png");
    updateRecipeCardImage(ui->recipeCard5, ":/sprites/Sprites/Cheeseburger.png");
    updateRecipeCardImage(ui->recipeCard6, ":/sprites/Sprites/Pancakes.png");

    // Signal connections for when the recipe is selected
    connect(ui->recipeCard1, &RecipeCardWidget::clicked, this, [this]() {
        onRecipeCardClicked(0);
    });
    connect(ui->recipeCard2, &RecipeCardWidget::clicked, this, [this]() {
        onRecipeCardClicked(1);
    });
    connect(ui->recipeCard3, &RecipeCardWidget::clicked, this, [this]() {
        onRecipeCardClicked(2);
    });
    connect(ui->recipeCard4, &RecipeCardWidget::clicked, this, [this]() {
        onRecipeCardClicked(3);
    });
    connect(ui->recipeCard5, &RecipeCardWidget::clicked, this, [this]() {
        onRecipeCardClicked(4);
    });
    connect(ui->recipeCard6, &RecipeCardWidget::clicked, this, [this]() {
        onRecipeCardClicked(5);
    });
}

void StartupScreen::updateRecipeCard(RecipeCardWidget* card, const QString& recipeName) {
    card->setRecipeName(recipeName);
}

void StartupScreen::updateRecipeCardImage(RecipeCardWidget* card, const QString& imagePath) {
    card->setRecipeImage(imagePath);
}
