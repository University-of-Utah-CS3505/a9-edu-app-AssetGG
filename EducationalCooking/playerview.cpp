#include "playerview.h"
#include "ui_playerview.h"

PlayerView::PlayerView(PlayerModel& model, QWidget *parent): QMainWindow(parent), ui(new Ui::PlayerView)
{
    ui->setupUi(this);
    connect(this, &PlayerView::didClickOnIngredient, &model, &PlayerModel::didClickOnIngredient);
    connect(this, &PlayerView::dropIngredient, &model, &PlayerModel::dropIngredient);
    connect(this, &PlayerView::updateIngredientPosition, &model, &PlayerModel::moveIngredientToPoint);
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
