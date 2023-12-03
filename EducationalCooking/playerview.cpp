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

    for (auto &[toolName, tool] : *tools) {
        QImage img = tool.GetImage();

        imagePainter.drawImage(QRect(tool.locX, tool.locY, img.width(), img.height()), img);
    }

    // Finally, ingredients.
    for (auto &[ingredientName, ingredient] : ingredientSprites) {
        QImage img = ingredient.GetImage();

        imagePainter.drawImage(QRect(ingredient.locX, ingredient.locY, img.width(), img.height()),
                               img);
    }
}

bool mouseOverSprite(QPoint mousePos, int x, int y, int w, int h)
{
    QRect spriteBounds(x, y, w, h);
    return spriteBounds.contains(mousePos);
}

void PlayerView::mousePressEvent(QMouseEvent *event)
{
    QPoint mousePos = event->pos();

    // check if we're clicking on any ingredients first.

    for (auto &[ingredientName, ingredient] : ingredientSprites) {
        QImage img = ingredient.GetImage();
        if (mouseOverSprite(mousePos, ingredient.locX, ingredient.locY, img.width(), img.height())) {
            emit itemGrabbed(ingredientName, mousePos);
            return;
        }
    }

    for (auto &[toolName, tool] : *tools) {
        QImage img = tool.GetImage();
        if (tool.IsMovable()) {
            if (mouseOverSprite(mousePos, tool.locX, tool.locY, img.width(), img.height())) {
                emit itemGrabbed(toolName, mousePos);
                return;
            }
        }
    }
}

void PlayerView::mouseMoveEvent(QMouseEvent *event)
{
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
        return &search->second;
}

void PlayerView::setupScene(Recipe &recipe, std::map<std::string, Tool> &tools)
{
    for (Ingredient &ingredient : recipe.getAvaliableIngredients()) {
        ingredientSprites.insert({ingredient.GetName(), ingredient});
    }

    this->tools = &tools;
}

void PlayerView::updateSpritePositions(
    const std::map<std::string, Physics::PhysicsObject> &physicsObjects)
{
    // for each physics object,
    for (const auto &[name, obj] : physicsObjects) {
        // check if it's an ingredient first
        auto ingredient = getIngredientByName(name);
        if (ingredient) {
            auto size = ingredient->GetImage().rect();
            ingredient->locX = obj.body->GetPosition().x - size.width() / 2.0;
            ingredient->locY = obj.body->GetPosition().y - size.height() / 2.0;
            continue;
        }
        // ok maybe it's a tool?
        auto tool = getToolByName(name);
        if (tool) {
            auto size = tool->GetImage().rect();
            tool->locX = obj.body->GetPosition().x - size.width() / 2.0;
            tool->locY = obj.body->GetPosition().y - size.height() / 2.0;
            continue;
        }
    }

    update();
}

void PlayerView::onScoreButtonClicked()
{
    emit calculateScoreRequested();

    // Blurs out the background
    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect;
    blurEffect->setBlurRadius(20);
    this->setGraphicsEffect(blurEffect);

    // Creation of final screen
    FinalScreen* finalScreen = new FinalScreen;
    finalScreen->show();

    ui->centralwidget->setGraphicsEffect(nullptr);
}
