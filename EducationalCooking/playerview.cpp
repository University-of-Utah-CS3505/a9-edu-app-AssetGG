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
}

PlayerView::~PlayerView()
{
    delete ui;
}

void PlayerView::paintEvent(QPaintEvent *event)
{
    QPainter imagePainter(this);
    imagePainter.drawImage(QRect(0, 0, 640, 640), QImage(":/sprites/Sprites/Kitchen.png"));

    for (auto &[spriteName, sprite] : ingredientSprites) {
        QImage img = sprite.GetImage();

        imagePainter.drawImage(QRect(sprite.locX, sprite.locY, img.width(), img.height()), img);
    }
}

void PlayerView::mousePressEvent(QMouseEvent *event)
{
    int mouseX = event->pos().x();
    int mouseY = event->pos().y();

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

//void PlayerView::mouseMoveEvent(QMouseEvent *event)
//{
//    if ((event->pos().x() >= tomato.locX - 50
//         && event->pos().x() <= (tomato.locX + tomato.GetImage().width()) + 50)
//        && (event->pos().y() >= tomato.locY - 50
//            && event->pos().y() <= (tomato.locY + tomato.GetImage().height() + 50))) {
//        tomato.locX = event->pos().x();
//        tomato.locY = event->pos().y();
//    }

//    update();
//}

Ingredient *PlayerView::getSpriteByName(std::string name)
{
    auto search = ingredientSprites.find(name);
    if (search == ingredientSprites.end())
        return nullptr;
    else
        return &search->second;
}

void PlayerView::setUpScene(Recipe &recipe)
{
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
            sprite->locX = obj.body->GetPosition().x;
            sprite->locY = obj.body->GetPosition().y;
        }
    }

    update();
}
