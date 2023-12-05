#include "finalscreen.h"
#include <QPixmap>
#include <QHBoxLayout>

FinalScreen::FinalScreen(QWidget *parent) : QWidget(parent) {
    setupLayout();
}

void FinalScreen::setScore(int score, const QString& recipeName) {
    currentRecipeName = recipeName;
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
    centerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(centerWidget);

    // Stars
    QHBoxLayout *starsLayout = new QHBoxLayout;
    starsLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    for (int i = 0; i < 5; ++i) {
        QLabel *star = new QLabel;
        QImage starImage(":/sprites/Sprites/Dorito.png");
        star->setPixmap(QPixmap::fromImage(starImage).scaled(40, 40));
        stars.push_back(star);
        stars[i]->setVisible(i < 100/20); // Todo: pass in score
        starsLayout->addWidget(star);
    }

    // Score
    scoreLabel = new QLabel(QString::number(100) + "/100"); // Todo: pass in score
    scoreLabel->setStyleSheet("font-size: 24pt;");
    scoreLabel->setAlignment(Qt::AlignHCenter);

    centerSection->addLayout(starsLayout);
    centerSection->addSpacing(-400);
    centerSection->addWidget(scoreLabel);

    // Initialize dishOrTrashLabel
    dishOrTrashLabel = new QLabel;
    dishOrTrashLabel->setAlignment(Qt::AlignHCenter);
    centerSection->addSpacing(-400);
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

void FinalScreen::displayDishOrTrash(int score) {
    QImage imageOfDish;

    if (score > 60) {
        if(currentRecipeName.toLower() == "spaghetti")
            imageOfDish = QImage(":/sprites/Sprites/Pasta Tomato.png");
        else if(currentRecipeName.toLower() == "salad")
            imageOfDish = QImage(":/sprites/Sprites/Salad Dish.png");
        else if(currentRecipeName.toLower() == "pepperoni pizza")
            imageOfDish = QImage(":/sprites/Sprites/Pepperoni Pizza.png");
        else if(currentRecipeName.toLower() == "soup")
            imageOfDish = QImage(":/sprites/Sprites/Chicken Soup.png");
        else if(currentRecipeName.toLower() == "hamburger")
            imageOfDish = QImage(":/sprites/Sprites/Cheeseburger.png");
        else if(currentRecipeName.toLower() == "pancakes")
            imageOfDish = QImage(":/sprites/Sprites/Pancakes.png");
    } else {
        imageOfDish = QImage(":/sprites/Sprites/Trash.png");
    }

    dishOrTrashLabel->setPixmap(QPixmap::fromImage(imageOfDish).scaled(200, 200));
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
