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
    updateRecipeCard(ui->recipeCard1, "Spaghetti");
    updateRecipeCard(ui->recipeCard2, "Salad");
    updateRecipeCard(ui->recipeCard3, "Pizza");
    updateRecipeCard(ui->recipeCard4, "Soup");
    updateRecipeCard(ui->recipeCard5, "Hamburger");
    updateRecipeCard(ui->recipeCard6, "Pancake");

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
