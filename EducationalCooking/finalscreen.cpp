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
    leftWidget->setStyleSheet("background-color: lightblue;");
    mainLayout->addWidget(leftWidget);

    // Center Section
    centerSection = new QVBoxLayout;
    centerWidget = new QWidget;
    centerWidget->setLayout(centerSection);
    centerWidget->setFixedSize(400, 600);
    centerWidget->setStyleSheet("background-color: lightgreen;");
    mainLayout->addWidget(centerWidget);

    // Stars
    QHBoxLayout *starsLayout = new QHBoxLayout;
    starsLayout->setAlignment(Qt::AlignTop);

    for (int i = 0; i < 5; ++i) {
        QLabel *star = new QLabel;
        QImage starImage(":/sprites/Sprites/Dorito.png");
        star->setPixmap(QPixmap::fromImage(starImage).scaled(40, 40));
        stars.push_back(star);
        starsLayout->addWidget(star);
    }

    centerSection->addLayout(starsLayout);

    // Initialize dishOrTrashLabel
    dishOrTrashLabel = new QLabel;
    centerSection->addWidget(dishOrTrashLabel);

    mainLayout->addWidget(centerWidget);

    // Right Section
    rightSection = new QVBoxLayout;
    rightWidget = new QWidget;
    rightSection->setAlignment(Qt::AlignTop);
    rightWidget->setLayout(rightSection);
    rightWidget->setFixedSize(200, 600);
    rightWidget->setStyleSheet("background-color: lightcoral;");
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
