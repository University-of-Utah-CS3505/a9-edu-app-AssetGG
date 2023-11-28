#include "recipecardwidget.h"
#include "ui_recipecardwidget.h"

RecipeCardWidget::RecipeCardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeCardWidget),
    selected(false)
{
    ui->setupUi(this);

    connect(ui->cardButton, &QPushButton::clicked, this, &RecipeCardWidget::clicked);
}

RecipeCardWidget::~RecipeCardWidget()
{
    delete ui;
}

void RecipeCardWidget::setRecipeName(const QString &name)
{
    ui->recipeLabel->setText(name);
}

bool RecipeCardWidget::isSelected() const
{
    return selected;
}

void RecipeCardWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    selected = !selected;

    if (selected)
        setStyleSheet("background-color: lightblue;");
    else
        setStyleSheet("background-color: white;");

    emit clicked();
}
