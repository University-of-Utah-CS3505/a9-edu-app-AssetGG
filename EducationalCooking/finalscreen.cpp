#include "finalscreen.h"
#include <QPixmap>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QProcess>

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

FinalScreen::FinalScreen(QWidget *parent) : QWidget(parent) {
    score = 100;

    setupLayout();
}

void FinalScreen::setScore(int scoreInput, vector<Ingredient> finalIngredients, const QString& recipeName) {
    score = scoreInput;

    updateLayout();

    currentRecipeName = recipeName;
    ingredients = finalIngredients;
    displayDishOrTrash(scoreInput);
    displayIngredients();

#ifdef Q_OS_WIN
    // Play the audio file on Windows
    PlaySound(L":/sprites/Sprites/Piss in soup.m4a", NULL, SND_ASYNC | SND_FILENAME);
#elif defined(Q_OS_MAC)
    QProcess::startDetached("afplay", QStringList() << "/sprites/Sprites/Piss-in-soup.wav");
#endif
}

void FinalScreen::setupLayout() {
    mainLayout = new QHBoxLayout(this);

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

    setLayout(mainLayout);
}

void FinalScreen::updateLayout() {
    // Stars
    QHBoxLayout *starsLayout = new QHBoxLayout;
    starsLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    for (int i = 0; i < 5; ++i) {
        QLabel *star = new QLabel;
        QImage starImage(":/sprites/Sprites/Dorito.png");
        star->setPixmap(QPixmap::fromImage(starImage).scaled(40, 40));
        stars.push_back(star);
        stars[i]->setVisible(i < score/20);
        starsLayout->addWidget(star);
    }

    // Score
    scoreLabel = new QLabel(QString::number(score) + "/100");
    scoreLabel->setStyleSheet("font-size: 24pt;");
    scoreLabel->setAlignment(Qt::AlignHCenter);


    // Initialize dishOrTrashLabel and gordonLabel
    gordonLabel = new QLabel;
    dishOrTrashLabel = new QLabel;

    gordonLabel->setAlignment(Qt::AlignHCenter);
    dishOrTrashLabel->setAlignment(Qt::AlignHCenter);

    gordonLabel->setPixmap(QPixmap::fromImage(QImage(":/sprites/Sprites/ramsay1.png")).scaled(300,300));

    centerSection->addLayout(starsLayout);
    centerSection->addSpacing(0);
    centerSection->addWidget(scoreLabel);
    centerSection->addSpacing(0);
    centerSection->addWidget(gordonLabel);
    centerSection->addSpacing(-100);
    centerSection->addWidget(dishOrTrashLabel);

    mainLayout->addWidget(centerWidget);

    setLayout(mainLayout);
}

void FinalScreen::displayDishOrTrash(int scoreInput) {
    QImage imageOfDish;

    if (scoreInput > 60) {
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
    QLayoutItem *child;
    while ((child = leftSection->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for (const auto& ingredient : ingredients) {
        QWidget* ingredientWidget = new QWidget;
        QHBoxLayout* ingredientLayout = new QHBoxLayout(ingredientWidget);

        QLabel* ingredientLabel = new QLabel;
        ingredientLabel->setText(QString::fromStdString(ingredient.GetName()));
        ingredientLabel->setAlignment(Qt::AlignCenter);
        ingredientLabel->setStyleSheet("font-size: 12pt;");
        ingredientLabel->setMinimumHeight(24);

        QLabel* ingredientImageLabel = new QLabel;
        ingredientImageLabel->setPixmap(QPixmap::fromImage(ingredient.GetImage()).scaled(24, 24));
        ingredientImageLabel->setMinimumHeight(24);

        ingredientLayout->addWidget(ingredientImageLabel);
        ingredientLayout->addWidget(ingredientLabel);

        leftSection->addWidget(ingredientWidget);
    }
}

void FinalScreen::addIngredient(const QString &name, const QString &imagePath) {
    QLabel *ingredientLabel = new QLabel;
    ingredientLabel->setText(name);
    ingredientLabel->setPixmap(QPixmap(imagePath));
    leftSection->addWidget(ingredientLabel);
}
