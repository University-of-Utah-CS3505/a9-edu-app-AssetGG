#include "playerview.h"
#include <QPainter>
#include "ingredient.h"
#include "physics.h"
#include "recipe.h"
#include "ui_playerview.h"
#include <map>
#include <vector>

PlayerView::PlayerView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlayerView)
{
    ui->setupUi(this);
    tomato = Ingredient("tomato",
                        QImage(":/sprites/Sprites/Tomato.png"),
                        QImage(":/sprites/Sprites/Tomato.png"),
                        QImage(":/sprites/Sprites/Tomato.png"),
                        true,
                        true,
                        125,
                        125);
    showRecipeHelp = false;
}

PlayerView::~PlayerView()
{
    delete ui;
}

void PlayerView::paintEvent(QPaintEvent *event)
{
    QPainter imagePainter(this);
    imagePainter.drawImage(QRect(0, 0, 640, 640), QImage(":/sprites/Sprites/Kitchen.png"));
    imagePainter.drawImage(QRect(240, 370, 50, 50), QImage(":/sprites/Sprites/recipeHelp.png"));

    for (auto &[spriteName, sprite] : ingredientSprites) {
        QImage img = sprite.GetImage();

        imagePainter.drawImage(QRect(sprite.locX, sprite.locY, img.width(), img.height()), img);
    }

    if(showRecipeHelp)
        imagePainter.drawImage(QRect(25, 100, 600, 600), QImage(":/sprites/Sprites/fullSizeRecipeHelp.png"));
}

void PlayerView::mousePressEvent(QMouseEvent *event)
{
    int mouseX = event->pos().x();
    int mouseY = event->pos().y();

    if (showRecipeHelp)
    {
        showRecipeHelp = false;
        recipeHelpLine1->setHidden(true);
        recipeHelpLine2->setHidden(true);
        recipeHelpLine3->setHidden(true);
        recipeHelpLine4->setHidden(true);
    }
    if (mouseX >= 240 && mouseX <= (240 + 50) && mouseY >= 370 && mouseY <= (370 + 50))
    {
        showRecipeHelp = true;
        recipeHelpLine1->setHidden(false);
        recipeHelpLine2->setHidden(false);
        recipeHelpLine3->setHidden(false);
        recipeHelpLine4->setHidden(false);
    }

    for (auto &[spriteName, sprite] : ingredientSprites) {
        if (mouseX >= sprite.locX && mouseX <= (sprite.locX + sprite.GetImage().width())) {
            if (mouseY >= sprite.locY && mouseY <= (sprite.locY + sprite.GetImage().height())) {
                emit ingredientGrabbed(spriteName, event->pos());
            }
        }
    }
}

void PlayerView::mouseMoveEvent(QMouseEvent *event)
{
    emit updateIngredientPosition(event->pos());
}

void PlayerView::mouseReleaseEvent(QMouseEvent *event)
{
    emit ingredientDropped(event->pos());
}

Ingredient *PlayerView::getSpriteByName(std::string name)
{
    auto search = ingredientSprites.find(name);
    if (search == ingredientSprites.end())
        return nullptr;
    else
        return &search->second;
}

void PlayerView::setupScene(Recipe &recipe)
{
    setupRecipeHelpLine1(recipe);
    setupRecipeHelpLine2(recipe);
    setupRecipeHelpLine3(recipe);
    setupRecipeHelpLine4(recipe);

    for (Ingredient &ingredient : recipe.getAvaliableIngredients()) {
        ingredientSprites.insert({ingredient.GetName(), ingredient});
    }
}

void PlayerView::updateSpritePositions(
    const std::map<std::string, Physics::PhysicsObject> &physicsObjects)
{
    for (const auto &[name, obj] : physicsObjects) {
        auto sprite = getSpriteByName(name);
        if (sprite) {
            auto size = sprite->GetImage().rect();
            sprite->locX = obj.body->GetPosition().x - size.width() / 2.0;
            sprite->locY = obj.body->GetPosition().y - size.height() / 2.0;
        }
    }

    update();
}

void PlayerView::setupRecipeHelpLine1(Recipe recipe)
{
    recipeHelpLine1 = new QLabel(this);

    recipeHelpLine1->setText(QString::fromStdString(recipe.getRecipeName()) + QString::fromStdString(" ingredients:\n"));
    recipeHelpLine1->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    recipeHelpLine1->setGeometry(QRect(175, 250, 350, 50));
    recipeHelpLine1->setHidden(true);
}

void PlayerView::setupRecipeHelpLine2(Recipe recipe)
{
    QString helpLine2Text = "";
    recipeHelpLine2 = new QLabel(this);

    for(Ingredient ingredient : recipe.getBaseIngredients())
        helpLine2Text += QString::fromStdString(ingredient.GetName()) + QString::fromStdString("--");

    recipeHelpLine2->setText(QString::fromStdString("--") + helpLine2Text + QString::fromStdString("\n"));
    recipeHelpLine2->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    recipeHelpLine2->setGeometry(QRect(175, 320, 350, 50));
    recipeHelpLine2->setHidden(true);
}

void PlayerView::setupRecipeHelpLine3(Recipe recipe)
{
    recipeHelpLine3 = new QLabel(this);
    recipeHelpLine3->setText(QString::fromStdString("Would any of these ingredients be good?-\n"));
    recipeHelpLine3->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    recipeHelpLine3->setGeometry(QRect(175, 400, 350, 50));
    recipeHelpLine3->setHidden(true);
}

void PlayerView::setupRecipeHelpLine4(Recipe recipe)
{
    QString helpLine4Text = "";
    recipeHelpLine4 = new QLabel(this);

    for(Ingredient ingredient : recipe.getBonusIngredients())
        helpLine4Text += ingredient.GetName() + "--";

    recipeHelpLine4->setText(QString::fromStdString("--") + helpLine4Text + QString::fromStdString("\n"));
    recipeHelpLine4->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    recipeHelpLine4->setGeometry(QRect(175, 500, 350, 50));
    recipeHelpLine4->setHidden(true);
}
