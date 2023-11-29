#include "playerview.h"
#include "ui_playerview.h"
#include <QPainter>
#include "ingredient.h"

PlayerView::PlayerView(PlayerModel &model, QWidget *parent): QMainWindow(parent), ui(new Ui::PlayerView)
{
    ui->setupUi(this);
    tomato = Ingredient("tomato", QImage(":/sprites/Sprites/Tomato.png"), QImage(":/sprites/Sprites/Tomato.png"), true, true, 125, 125);

    //connect(this, &PlayerView::didClickOnIngredient, &model, &PlayerModel::didClickOnIngredient);
    //connect(this, &PlayerView::dropIngredient, &model, &PlayerModel::dropIngredient);
    //connect(this, &PlayerView::updateIngredientPosition, &model, &PlayerModel::moveIngredientToPoint);
    //connect(&model, &PlayerModel::moveClickedIngredient, this, &PlayerView::moveClickedIngredient);
}

PlayerView::~PlayerView()
{
    delete ui;
}

void PlayerView::paintEvent(QPaintEvent *event)
{
    QPainter imagePainter(this);
    imagePainter.drawImage(QRect(0, 0, 640, 640), QImage(":/sprites/Sprites/Kitchen.png"));
    imagePainter.drawImage(QRect(tomato.locX, tomato.locY, tomato.GetImage().height(), tomato.GetImage().width()), tomato.GetImage());
}

void PlayerView::mousePressEvent(QMouseEvent *event)
{
}

void PlayerView::mouseReleaseEvent(QMouseEvent *event)
{
}

void PlayerView::mouseMoveEvent(QMouseEvent *event)
{
    tomato.locX = event->pos().x();
    tomato.locY = event->pos().y();
    update();
}

