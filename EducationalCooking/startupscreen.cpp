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
    PlayerView* playerView = new PlayerView(playerModel);
    playerView->show(); // Shows playerView after recipe is selected

    this->hide();
}

void StartupScreen::createRecipeCards() {
    // Instances of recipe cards
    RecipeCardWidget* spaghetti = new RecipeCardWidget(this);
    RecipeCardWidget* salad = new RecipeCardWidget(this);
    RecipeCardWidget* pizza = new RecipeCardWidget(this);
    RecipeCardWidget* soup = new RecipeCardWidget(this);
    RecipeCardWidget* hamburger = new RecipeCardWidget(this);
    RecipeCardWidget* pancake = new RecipeCardWidget(this);

    QVBoxLayout* verticalLayout = new QVBoxLayout;

    // Set properties for recipe name
    spaghetti->setRecipeName("Spaghetti");
    salad->setRecipeName("Salad");
    pizza->setRecipeName("Pizza");
    soup->setRecipeName("Soup");
    hamburger->setRecipeName("Hamburger");
    pancake->setRecipeName("Pancake");

    // Add recipes to layout
    verticalLayout->addWidget(spaghetti);
    verticalLayout->addWidget(salad);
    verticalLayout->addWidget(pizza);
    verticalLayout->addWidget(soup);
    verticalLayout->addWidget(hamburger);
    verticalLayout->addWidget(pancake);

    ui->verticalLayout->addLayout(verticalLayout);

    // Signal connections for when the recipe is selected
    connect(spaghetti, &RecipeCardWidget::clicked, this, [this]() {
        onRecipeCardClicked(0);
    });
    connect(salad, &RecipeCardWidget::clicked, this, [this]() {
        onRecipeCardClicked(1);
    });
    connect(pizza, &RecipeCardWidget::clicked, this, [this]() {
        onRecipeCardClicked(2);
    });
    connect(soup, &RecipeCardWidget::clicked, this, [this]() {
        onRecipeCardClicked(3);
    });
    connect(hamburger, &RecipeCardWidget::clicked, this, [this]() {
        onRecipeCardClicked(4);
    });
    connect(pancake, &RecipeCardWidget::clicked, this, [this]() {
        onRecipeCardClicked(5);
    });
}
