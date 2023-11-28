#include "playerview.h"
#include "ui_playerview.h"

PlayerView::PlayerView(PlayerModel& model, QWidget *parent): QMainWindow(parent), ui(new Ui::PlayerView)
{
    ui->setupUi(this);
}

PlayerView::~PlayerView()
{
    delete ui;
}

void PlayerView::paintEvent(QPaintEvent *event) {

}
