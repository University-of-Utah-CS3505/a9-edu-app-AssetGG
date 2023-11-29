#include "playerview.h"
#include "ui_playerview.h"
#include <QPainter>
#include <vector>
#include "ingredient.h"

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

