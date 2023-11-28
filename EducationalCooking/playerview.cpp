#include "playerview.h"
#include "ui_playerview.h"

PlayerView::PlayerView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlayerView)
{
    ui->setupUi(this);
}

PlayerView::~PlayerView()
{
    delete ui;
}

void PlayerView::paintEvent(QPaintEvent *event) {}

void PlayerView::mousePressEvent(QMouseEvent *event)
{
    emit didClickOnIngredient(event->pos());
}

void PlayerView::mouseReleaseEvent(QMouseEvent *event)
{
    emit unclickIngredient(event->pos());
}

void PlayerView::mouseMoveEvent(QMouseEvent *event)
{
    emit updateIngredientPosition(event->pos());
}
