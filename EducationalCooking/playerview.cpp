#include "playerview.h"
#include <QPainter>
#include "ingredient.h"
#include "physics.h"
#include "recipe.h"
#include "ui_playerview.h"
#include "finalscreen.h"
#include <map>
#include <vector>
#include <QGraphicsBlurEffect>

PlayerView::PlayerView(QWidget *parent)
    : QMainWindow(parent)
    , tools(nullptr)
    , ui(new Ui::PlayerView)
{
    ui->setupUi(this);

    showRecipeHelp = false;

    connect(ui->scoreButton, &QPushButton::clicked, this, &PlayerView::onScoreButtonClicked);
}

PlayerView::~PlayerView()
{
    delete ui;
}

void PlayerView::paintEvent(QPaintEvent *event)
{
    QPainter imagePainter(this);
    // draw the things that need to show up on top last. Background goes first.
    imagePainter.drawImage(QRect(0, 0, 640, 640), QImage(":/sprites/Sprites/Kitchen.png"));
    imagePainter.drawImage(QRect(240, 550, chosenRecipe.getSmallHelpSprite().width() * 2,
                           chosenRecipe.getSmallHelpSprite().height() * 2), chosenRecipe.getSmallHelpSprite());

    for (auto &[toolName, tool] : *tools)
    {
        QImage img = tool->GetImage();

        imagePainter.drawImage(QRect(tool->locX, tool->locY, img.width(), img.height()), img);
    }

    // Finally, ingredients.
    for (auto &[ingredientName, ingredient] : ingredientSprites)
    {
        QImage img = ingredient.GetImage();

        imagePainter.drawImage(QRect(ingredient.locX, ingredient.locY, img.width(), img.height()), img);
    }

    if(showRecipeHelp)
        imagePainter.drawImage(QRect(25, 100, chosenRecipe.getLargeHelpSprite().width() * 6,
                                     chosenRecipe.getLargeHelpSprite().height() * 6), chosenRecipe.getLargeHelpSprite());
}

bool mouseOverSprite(QPoint mousePos, int x, int y, int w, int h)
{
    QRect spriteBounds(x, y, w, h);
    return spriteBounds.contains(mousePos);
}

void PlayerView::mousePressEvent(QMouseEvent *event)
{
    QPoint mousePos = event->pos();

    if(showRecipeHelp)
    {
        showRecipeHelp = false;
        recipeHelpLine1->setHidden(true);
        recipeHelpLine2->setHidden(true);
        recipeHelpLine3->setHidden(true);
        recipeHelpLine4->setHidden(true);
    }

    if(mouseOverSprite(mousePos, 240, 550, chosenRecipe.getSmallHelpSprite().width() * 2, chosenRecipe.getSmallHelpSprite().height() * 2))
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
        QImage img = ingredient.GetImage();
        if (mouseOverSprite(mousePos, ingredient.locX, ingredient.locY, img.width(), img.height()))
        {
            clickedIngredient = ingredient;
            emit itemGrabbed(ingredientName, true, mousePos);
            return;
        }
    }

    for (auto &[toolName, tool] : *tools)
    {
        QImage img = tool->GetImage();
        if (tool->IsMovable()) {
            if (mouseOverSprite(mousePos, tool->locX, tool->locY, img.width(), img.height())) {
                emit itemGrabbed(toolName, false, mousePos);
                return;
            }
        }
    }
}

void PlayerView::mouseMoveEvent(QMouseEvent *event)
{
    QRect placeFinishedIngredients(0, 0, 20, 20);

    if (placeFinishedIngredients.contains(event->pos()))
    {
        QLabel* addedSomethingToDishLabel = new QLabel(this);
        addedSomethingToDishLabel->setText("+" + QString(QString::fromStdString(clickedIngredient.GetName())));
        addedSomethingToDishLabel->setGeometry(QRect(15, 0, 100, 20));
        addedSomethingToDishLabel->setHidden(false);
        ingredientSprites.erase(clickedIngredient.GetName());
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
    setupRecipeHelpLine3(recipe);
    setupRecipeHelpLine4(recipe);

    for (Ingredient &ingredient : recipe.getAvaliableIngredients())
    {
        ingredientSprites.insert({ingredient.GetName(), ingredient});
    }

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
            auto size = ingredient->GetImage().rect();
            ingredient->locX = obj.body->GetPosition().x - size.width() / 2.0;
            ingredient->locY = obj.body->GetPosition().y - size.height() / 2.0;
            continue;
        }
        // ok maybe it's a tool?
        auto tool = getToolByName(name);
        if (tool)
        {
            auto size = tool->GetImage().rect();
            tool->locX = obj.body->GetPosition().x - size.width() / 2.0;
            tool->locY = obj.body->GetPosition().y - size.height() / 2.0;
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
    recipeHelpLine1->setGeometry(QRect(165, 250, 350, 50));
    recipeHelpLine1->setHidden(true);
}

void PlayerView::setupRecipeHelpLine2(Recipe recipe)
{
    QString helpLine2Text = "";
    recipeHelpLine2 = new QLabel(this);

    for(ComparisonIngredient ingredient : recipe.getBaseIngredients())
        helpLine2Text += QString::fromStdString(ingredient.GetName()) + QString::fromStdString("--");

    recipeHelpLine2->setText(QString::fromStdString("--") + helpLine2Text + QString::fromStdString("\n"));
    recipeHelpLine2->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    recipeHelpLine2->setGeometry(QRect(165, 275, 550, 50));
    recipeHelpLine2->setHidden(true);
}

void PlayerView::setupRecipeHelpLine3(Recipe recipe)
{
    recipeHelpLine3 = new QLabel(this);
    recipeHelpLine3->setText(QString::fromStdString("Would any of these ingredients be good?\n"));
    recipeHelpLine3->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    recipeHelpLine3->setGeometry(QRect(125, 350, 350, 50));
    recipeHelpLine3->setHidden(true);
}

void PlayerView::setupRecipeHelpLine4(Recipe recipe)
{
    QString helpLine4Text = "";
    recipeHelpLine4 = new QLabel(this);

    for(ComparisonIngredient ingredient : recipe.getBonusIngredients())
        helpLine4Text += ingredient.GetName() + "--";

    recipeHelpLine4->setText(QString::fromStdString("--") + helpLine4Text + QString::fromStdString("\n"));
    recipeHelpLine4->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    recipeHelpLine4->setGeometry(QRect(125, 380, 550, 50));
    recipeHelpLine4->setHidden(true);
}

void PlayerView::onScoreButtonClicked()
{
    emit calculateScoreRequested();

    // Creation of final screen
    FinalScreen* finalScreen = new FinalScreen;
    finalScreen->show();

    this->close();
}
