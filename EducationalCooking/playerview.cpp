#include "playerview.h"
#include "ui_playerview.h"
#include <QPainter>
#include <vector>
#include <map>
#include "ingredient.h"
#include "physics.h"

PlayerView::PlayerView(QWidget *parent): QMainWindow(parent), ui(new Ui::PlayerView)
{
    ui->setupUi(this);
    std::vector<Ingredient> vect;
    setUpView(vect);
}

PlayerView::~PlayerView()
{
    delete ui;
}

void PlayerView::paintEvent(QPaintEvent *event)
{
    QPainter imagePainter(this);
    imagePainter.drawImage(QRect(0, 0, 640, 640), QImage(":/sprites/Sprites/Kitchen.png"));
    imagePainter.drawImage(QRect(tomato.locX, tomato.locY, tomato.GetImage().width(), tomato.GetImage().height()), tomato.GetImage());
}

void PlayerView::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->pos().x() >= tomato.locX - 50 && event->pos().x() <= (tomato.locX + tomato.GetImage().width()) + 50)
        && (event->pos().y() >= tomato.locY - 50 && event->pos().y() <= (tomato.locY + tomato.GetImage().height() + 50)))
    {
        tomato.locX = event->pos().x();
        tomato.locY = event->pos().y();
    }

//    tomato.locX = event->pos().x();
//    tomato.locY = event->pos().y();
    update();
}

void PlayerView::setUpView(std::vector<Ingredient>)
{
    tomato = Ingredient("tomato", QImage(":/sprites/Sprites/Tomato.png"), QImage(":/sprites/Sprites/Tomato.png"), QImage(":/sprites/Sprites/Tomato.png"), true, true, 125, 125);
}

void updateSpritePositions(const std::map<std::string, Physics::PhysicsObject> &physicsObjects)
{
  //for (const auto&[name, physicsObject]: physicsObjects) {

  //}
    Physics::PhysicsObject *obj = physicsObjects.at("tomato");
    Ingredient sprite = tomato;//getSpriteByName(name);
    sprite.locX = obj.body.position.x;
    sprite.locY = obj.body.position.y;
}

