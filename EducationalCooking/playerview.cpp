/*
 * Name: Everyone
 * Reviewed By: Nathaniel Taylor
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: Handles the data and operations for UI components of the game.
 * Including, but not limited to, user input events, scene drawing,
 * and the recipe help button.
 */

#include "playerview.h"
#include <QPainter>
#include "ingredient.h"
#include "physics.h"
#include "recipe.h"
#include "ui_playerview.h"
#include "finalscreen.h"
#include <QGraphicsBlurEffect>
#include <iostream>
#include <QToolTip>

PlayerView::PlayerView(QWidget *parent)
    : QMainWindow(parent)
    , tools(nullptr)
    , ui(new Ui::PlayerView)
{
    ui->setupUi(this);

    showRecipeHelp = false;
    finalDishBowl = QImage(":/sprites/Sprites/bowl.png");
    addedSomethingToDishLabel = new QLabel(this);

    connect(ui->scoreButton, &QPushButton::clicked, this, &PlayerView::onScoreButtonClicked);
    connect(&hideLabelTimer, &QTimer::timeout, this, &PlayerView::hideIngredientAdded);
}

PlayerView::~PlayerView()
{
    delete ui;
}

void PlayerView::paintEvent(QPaintEvent *) //QPaintEvent parameter never used so no name is needed
{
    QPainter imagePainter(this);
    // draw the things that need to show up on top last. Background goes first.
    imagePainter.drawImage(QRect(0, 0, 640, 640), QImage(":/sprites/Sprites/Kitchen.png"));
    imagePainter.drawImage(QRect(240, 550, chosenRecipe.getSmallHelpSprite().width() * 2,
                           chosenRecipe.getSmallHelpSprite().height() * 2), chosenRecipe.getSmallHelpSprite());
    imagePainter.drawImage(QRect(50, 450, finalDishBowl.width() * 2.5, finalDishBowl.height() * 2.5), finalDishBowl);

    for (auto &[toolName, tool] : *tools)
    {
        QImage image = tool->getImage();

        imagePainter.drawImage(QRect(tool->xLocation, tool->yLocation, image.width(), image.height()), image);
    }

    // Finally, ingredients.
    for (auto &[ingredientName, ingredient] : ingredientSprites)
    {
        QImage image = ingredient.getImage();

        imagePainter.drawImage(QRect(ingredient.xLocation, ingredient.yLocation, image.width(), image.height()), image);
    }

    if(showRecipeHelp)
        imagePainter.drawImage(QRect(25, 100, chosenRecipe.getLargeHelpSprite().width() * 6,
                                     chosenRecipe.getLargeHelpSprite().height() * 6), chosenRecipe.getLargeHelpSprite());
}

bool mouseOverSprite(QPoint mousePos, int xLoc, int yLoc, int width, int height)
{
    QRect spriteBounds(xLoc, yLoc, width, height);
    return spriteBounds.contains(mousePos);
}

void PlayerView::mousePressEvent(QMouseEvent *event)
{
    QPoint mousePosition = event->pos();

    if(showRecipeHelp)
    {
        showRecipeHelp = false;
        recipeHelpLine1->setHidden(true);
        recipeHelpLine2->setHidden(true);
        recipeHelpLine3->setHidden(true);
        recipeHelpLine4->setHidden(true);
    }

    if(mouseOverSprite(mousePosition, 240, 550, chosenRecipe.getSmallHelpSprite().width() * 2, chosenRecipe.getSmallHelpSprite().height() * 2))
    {
        showRecipeHelp = true;
        recipeHelpLine1->setHidden(false);
        recipeHelpLine2->setHidden(false);
        recipeHelpLine3->setHidden(false);
        recipeHelpLine4->setHidden(false);
    }

    // check if we're clicking on any ingredient.
    for (auto &[ingredientName, ingredient] : ingredientSprites)
    {
        QImage image = ingredient.getImage();
        if (mouseOverSprite(mousePosition, ingredient.xLocation, ingredient.yLocation, image.width(), image.height()))
        {
            QToolTip::showText(QPoint(ingredient.xLocation + 10, ingredient.yLocation), QString::fromStdString(ingredient.getName()));

            clickedIngredient = ingredient;
            emit itemGrabbed(ingredientName, true, mousePosition);
            return;
        }
    }

    for (auto &[toolName, tool] : *tools)
    {
        QImage image = tool->getImage();
        if (tool->isMovable())
        {
            if (mouseOverSprite(mousePosition, tool->xLocation, tool->yLocation, image.width(), image.height()))
            {
                emit itemGrabbed(toolName, false, mousePosition);
                return;
            }
        }
    }
}

void PlayerView::mouseMoveEvent(QMouseEvent *event)
{
    QRect placeFinishedIngredients(40, 450, finalDishBowl.width() * 2.25, finalDishBowl.height() * 2.25);

    if (placeFinishedIngredients.contains(event->pos()))
    {
        addedSomethingToDishLabel->setText("+" + QString(QString::fromStdString(clickedIngredient.getName())));
        addedSomethingToDishLabel->setGeometry(QRect(125, 475, 100, 20));
        addedSomethingToDishLabel->setHidden(false);
        hideLabelTimer.start(500);
        ingredientSprites.erase(clickedIngredient.getName());
        emit addItemToFinalDishIngredients(clickedIngredient);
    }
    emit updateDragPosition(event->pos());
}

void PlayerView::mouseReleaseEvent(QMouseEvent *event)
{
    emit itemDropped(event->pos());
}

Ingredient *PlayerView::getIngredientByName(std::string name)
{
    auto search = ingredientSprites.find(name);
    if (search == ingredientSprites.end())
        return nullptr;
    else
        return &search->second;
}

Tool *PlayerView::getToolByName(std::string name)
{
    auto search = tools->find(name);
    if (search == tools->end())
        return nullptr;
    else
        return search->second;
}

void PlayerView::setupScene(Recipe &recipe, std::map<std::string, Tool*> &tools)
{
    chosenRecipe = recipe;
    setupRecipeHelpLine1(recipe);
    setupRecipeHelpLine2(recipe);
    setupRecipeHelpLine3();
    setupRecipeHelpLine4(recipe);

    for (Ingredient &ingredient : recipe.getAvaliableIngredients())
        ingredientSprites.insert({ingredient.getName(), ingredient});

    this->tools = &tools;
}

void PlayerView::updateSpritePositions(const std::map<std::string, Physics::PhysicsObject> &physicsObjects)
{
    // for each physics object,
    for (const auto &[name, obj] : physicsObjects)
    {
        // check if it's an ingredient first
        auto ingredient = getIngredientByName(name);
        if (ingredient)
        {
            auto size = ingredient->getImage().rect();
            ingredient->xLocation = obj.body->GetPosition().x - size.width() / 2.0;
            ingredient->yLocation = obj.body->GetPosition().y - size.height() / 2.0;
            continue;
        }

        // ok maybe it's a tool?
        auto tool = getToolByName(name);
        if (tool)
        {
            auto size = tool->getImage().rect();
            tool->xLocation = obj.body->GetPosition().x - size.width() / 2.0;
            tool->yLocation = obj.body->GetPosition().y - size.height() / 2.0;
            continue;
        }
    }

    update();
}

void PlayerView::setupRecipeHelpLine1(Recipe recipe)
{
    recipeHelpLine1 = new QLabel(this);

    recipeHelpLine1->setText(QString::fromStdString(recipe.getRecipeName()) + QString::fromStdString(" Ingredients:\n"));
    recipeHelpLine1->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    recipeHelpLine1->setGeometry(QRect(165, 250, 350, 35));
    recipeHelpLine1->setHidden(true);
}

void PlayerView::setupRecipeHelpLine2(Recipe recipe)
{
    QString helpLine2Text = "";
    recipeHelpLine2 = new QLabel(this);

    for(ComparisonIngredient ingredient : recipe.getBaseIngredients())
    {
        helpLine2Text += QString::fromStdString(ingredient.getName()) + QString::fromStdString("--");

        if (ingredient.isCut() == true)
            helpLine2Text += QString::fromStdString("cut") + QString::fromStdString("--");
        if (ingredient.isCooked() == true)
            helpLine2Text += QString::fromStdString("cooked") + "--";

        helpLine2Text += "\n";
    }

    recipeHelpLine2->setText(helpLine2Text + QString::fromStdString("\n"));
    recipeHelpLine2->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    recipeHelpLine2->setGeometry(QRect(165, 275, 550, 75));
    recipeHelpLine2->setHidden(true);
}

void PlayerView::setupRecipeHelpLine3()
{
    recipeHelpLine3 = new QLabel(this);
    recipeHelpLine3->setText(QString::fromStdString("Would any of these ingredients be good?\n"));
    recipeHelpLine3->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    recipeHelpLine3->setGeometry(QRect(125, 350, 350, 35));
    recipeHelpLine3->setHidden(true);
}

void PlayerView::setupRecipeHelpLine4(Recipe recipe)
{
    QString helpLine4Text = "";
    recipeHelpLine4 = new QLabel(this);

    for(ComparisonIngredient ingredient : recipe.getBonusIngredients())
        helpLine4Text += "--" + ingredient.getName() + "\n";

    recipeHelpLine4->setText(helpLine4Text + QString::fromStdString("\n"));
    recipeHelpLine4->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    recipeHelpLine4->setGeometry(QRect(125, 375, 550, 85));
    recipeHelpLine4->setHidden(true);
}

void PlayerView::onScoreButtonClicked()
{
    int score = emit calculateScoreRequested();
    vector<Ingredient> ingredients = emit getFinalIngredientsRequested();

    // Creation of final screen
    FinalScreen* finalScreen = new FinalScreen;
    finalScreen->setScore(score, ingredients, QString::fromStdString(chosenRecipe.getRecipeName()));
    finalScreen->show();

    this->close();
}

void PlayerView::hideIngredientAdded()
{
    addedSomethingToDishLabel->setHidden(true);
}
