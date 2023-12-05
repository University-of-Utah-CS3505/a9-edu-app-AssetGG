#include "finalscreen.h"
#include <QPixmap>
#include <QHBoxLayout>

FinalScreen::FinalScreen(QWidget *parent) : QWidget(parent) {
    setupLayout();
}

void FinalScreen::setScore(int score) {
    displayStars(score);
    displayDishOrTrash(score);
    displayIngredients();
}

void FinalScreen::setupLayout() {
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // Left Section
    leftSection = new QVBoxLayout;
    leftWidget = new QWidget;
    leftSection->setAlignment(Qt::AlignTop);
    leftWidget->setLayout(leftSection);
    leftWidget->setFixedSize(200, 600);
    mainLayout->addWidget(leftWidget);

    // Center Section
    centerSection = new QVBoxLayout;
    centerWidget = new QWidget;
    centerWidget->setLayout(centerSection);
    centerWidget->setFixedSize(400, 600);
    mainLayout->addWidget(centerWidget);

    // Right Section
    rightSection = new QVBoxLayout;
    rightWidget = new QWidget;
    rightSection->setAlignment(Qt::AlignTop);
    rightWidget->setLayout(rightSection);
    rightWidget->setFixedSize(200, 600);
    mainLayout->addWidget(rightWidget);

    setLayout(mainLayout);

}

void FinalScreen::displayStars(int score) {
    int numberOfStars = score / 20;
    for (int i = 0; i < 5; ++i) {
        stars[i]->setVisible(i < numberOfStars);
    }
}

void FinalScreen::displayDishOrTrash(int score) {
    QString imagePath = (score > 60) ? ":/images/dish.png" : ":/images/trash.png";
    dishOrTrashLabel->setPixmap(QPixmap(imagePath));
}

void FinalScreen::displayIngredients() {
    addIngredient("Tomato", ":/ingredients/tomato.png");
    addIngredient("Onion", ":/ingredients/onion.png");
    addIngredient("Cheese", ":/ingredients/cheese.png");
}

void FinalScreen::addIngredient(const QString &name, const QString &imagePath) {
    QLabel *ingredientLabel = new QLabel;
    ingredientLabel->setText(name);
    ingredientLabel->setPixmap(QPixmap(imagePath));
    leftSection->addWidget(ingredientLabel);
}
