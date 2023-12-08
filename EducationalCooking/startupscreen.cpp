#include "startupscreen.h"
#include "playerview.h"
#include <QStyle>
#include "recipecardwidget.h"
#include "ui_startupscreen.h"

StartupScreen::StartupScreen(PlayerModel &model, PlayerView &view, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartupScreen)
    , playerView(view)
    , playerModel(model)
{
    ui->setupUi(this);

    recipeCards << ui->recipeCard1 << ui->recipeCard2 << ui->recipeCard3 << ui->recipeCard4 << ui->recipeCard5 << ui->recipeCard6;

    connect(ui->recipeCard1, &RecipeCardWidget::clicked, this, [this]() { handleRecipeCardClicked(ui->recipeCard1->getRecipeName()); });
    connect(ui->recipeCard2, &RecipeCardWidget::clicked, this, [this]() { handleRecipeCardClicked(ui->recipeCard2->getRecipeName()); });
    connect(ui->recipeCard3, &RecipeCardWidget::clicked, this, [this]() { handleRecipeCardClicked(ui->recipeCard3->getRecipeName()); });
    connect(ui->recipeCard4, &RecipeCardWidget::clicked, this, [this]() { handleRecipeCardClicked(ui->recipeCard4->getRecipeName()); });
    connect(ui->recipeCard5, &RecipeCardWidget::clicked, this, [this]() { handleRecipeCardClicked(ui->recipeCard5->getRecipeName()); });
    connect(ui->recipeCard6, &RecipeCardWidget::clicked, this, [this]() { handleRecipeCardClicked(ui->recipeCard6->getRecipeName()); });

    connect(ui->learnRecipeButton,
            &QPushButton::clicked,
            this,
            &StartupScreen::onLearnRecipeClicked);

    createRecipeCards();
}

StartupScreen::~StartupScreen()
{
    delete ui;
}

void StartupScreen::onLearnRecipeClicked()
{
    playerModel.setupScene();
    playerView.setupScene(playerModel.getSelectedRecipe(), playerModel.getTools());
    playerView.show(); // Shows playerView after recipe is selected
    this->hide();
}

void StartupScreen::createRecipeCards()
{
    recipeCardImage1 = QImage(":/sprites/Sprites/Pasta Tomato.png");
    recipeCardImage2 = QImage(":/sprites/Sprites/Salad Dish.png");
    recipeCardImage3 = QImage(":/sprites/Sprites/Pepperoni Pizza.png");
    recipeCardImage4 = QImage(":/sprites/Sprites/Chicken Soup.png");
    recipeCardImage5 = QImage(":/sprites/Sprites/Cheeseburger.png");
    recipeCardImage6 = QImage(":/sprites/Sprites/Pancakes.png");

    updateRecipeCard(ui->recipeCard1, "Spaghetti");
    updateRecipeCard(ui->recipeCard2, "Salad");
    updateRecipeCard(ui->recipeCard3, "Pepperoni Pizza");
    updateRecipeCard(ui->recipeCard4, "Soup");
    updateRecipeCard(ui->recipeCard5, "Hamburger");
    updateRecipeCard(ui->recipeCard6, "Pancake");

    // Update recipe images
    updateRecipeCardImage(ui->recipeCard1, ":/sprites/Sprites/Spaghetti and Meatballs.png");
    updateRecipeCardImage(ui->recipeCard2, ":/sprites/Sprites/Salad Dish.png");
    updateRecipeCardImage(ui->recipeCard3, ":/sprites/Sprites/Pepperoni Pizza.png");
    updateRecipeCardImage(ui->recipeCard4, ":/sprites/Sprites/Chicken Soup.png");
    updateRecipeCardImage(ui->recipeCard5, ":/sprites/Sprites/Cheeseburger.png");
    updateRecipeCardImage(ui->recipeCard6, ":/sprites/Sprites/Pancakes.png");

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

void StartupScreen::updateRecipeCard(RecipeCardWidget *card, const QString &recipeName)
{
    card->setRecipeName(recipeName);
}

void StartupScreen::updateRecipeCardImage(RecipeCardWidget *card, const QString &imagePath)
{
    card->setRecipeImage(imagePath);
}

void StartupScreen::handleRecipeCardClicked(const QString &recipeName) {
    playerModel.setCurrentRecipe(recipeName);
}

void StartupScreen::onRecipeCardClicked(int recipeIndex) {
    for (int i = 0; i < recipeCards.size(); ++i)
    {
        if (i == recipeIndex)
        {
            recipeCards[i]->setProperty("selected", true);
            recipeCards[i]->setStyleSheet("border: 4px solid #4287f5; border-radius: 10px;");
        }
        else
        {
            recipeCards[i]->setProperty("selected", false);
            recipeCards[i]->setStyleSheet("");
        }

        recipeCards[i]->style()->polish(recipeCards[i]);
    }
}
