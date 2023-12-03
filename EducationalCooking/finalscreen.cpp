#include "finalscreen.h"
#include "ui_finalscreen.h"

FinalScreen::FinalScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FinalScreen)
{
    ui->setupUi(this);
}

FinalScreen::~FinalScreen()
{
    delete ui;
}
