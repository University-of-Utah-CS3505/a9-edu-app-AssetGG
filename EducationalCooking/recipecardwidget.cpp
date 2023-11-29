#include "recipecardwidget.h"
#include "ui_recipecardwidget.h"

RecipeCardWidget::RecipeCardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeCardWidget),
    selected(false)
{
    ui->setupUi(this);
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

void RecipeCardWidget::setRecipeImage(const QString &imagePath)
{
    QPixmap image(imagePath);
    ui->recipeImageLabel->setPixmap(image.scaledToHeight(80));
}

void RecipeCardWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    onCardClicked();


    emit clicked();
}

QString RecipeCardWidget::getRecipeName()
{
    return ui->recipeLabel->text();
}

void RecipeCardWidget::onCardClicked()
{
    QString recipeName = ui->recipeLabel->text();

    emit recipeClicked(recipeName);
}
