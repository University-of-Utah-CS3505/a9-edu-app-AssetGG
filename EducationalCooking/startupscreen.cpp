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

    connect(ui->learnRecipeButton, &QPushButton::clicked, this, &StartupScreen::onLearnRecipeClicked);
}

StartupScreen::~StartupScreen() {
    delete ui;
}

void StartupScreen::onRecipeCardClicked(int recipeIndex) {
    //Todo: update selected recipe
}

void StartupScreen::onLearnRecipeClicked() {
    PlayerView* playerView = new PlayerView(playerModel);
    playerView->show(); // Shows playerView after recipe is selected

    this->hide();
}
