#include "playerview.h"
#include "ui_playerview.h"
#include <QPainter>

PlayerView::PlayerView(QWidget *parent): QMainWindow(parent), ui(new Ui::PlayerView)
{
    ui->setupUi(this);
}

PlayerView::~PlayerView()
{
    delete ui;
}

void PlayerView::paintEvent(QPaintEvent *event)
{

}

void PlayerView::mousePressEvent(QMouseEvent *event)
{
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
