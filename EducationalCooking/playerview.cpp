#include "playerview.h"
#include "ui_playerview.h"
#include <QPainter>
#include "ingredient.h"

PlayerView::PlayerView(QWidget *parent): QMainWindow(parent), ui(new Ui::PlayerView)
{
    ui->setupUi(this);
    tomato = Ingredient("tomato", QImage(":/sprites/Sprites/Tomato.png"), QImage(":/sprites/Sprites/Tomato.png"), true, true, 125, 125);
}

PlayerView::~PlayerView()
{
    delete ui;
}

void PlayerView::paintEvent(QPaintEvent *event)
{
    QPainter imagePainter(this);
    imagePainter.drawImage(QRect(0, 0, 640, 640), QImage(":/sprites/Sprites/Kitchen.png"));
    imagePainter.drawImage(tomato.GetRect(), tomato.GetImage());
}

void PlayerView::mousePressEvent(QMouseEvent *event)
{
    update();
    emit didClickOnIngredient(event->pos());
}

void PlayerView::mouseReleaseEvent(QMouseEvent *event)
{
    emit dropIngredient(event->pos());
}

void PlayerView::mouseMoveEvent(QMouseEvent *event)
{
    emit updateIngredientPosition(event->pos());
}

void PlayerView::updateClickedIngredient(QImage* ingredient, int x, int y)
{
    ingredient.
    update();
}
