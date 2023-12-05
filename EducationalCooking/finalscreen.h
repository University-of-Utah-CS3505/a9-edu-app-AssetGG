#ifndef FINALSCREEN_H
#define FINALSCREEN_H

#include "ingredient.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

using std::vector;

class FinalScreen : public QWidget {
    Q_OBJECT

public:
    FinalScreen(QWidget *parent = nullptr);

    void setScore(int score, vector<Ingredient> ingredients, const QString& recipeName);

private:
    void setupLayout();
    void updateLayout();
    void displayDishOrTrash(int score);
    void displayIngredients();
    void addIngredient(const QString &name, const QString &imagePath);
    vector<Ingredient> ingredients;
    QString currentRecipeName;

    int score;

    QHBoxLayout *mainLayout;

    QVBoxLayout *leftSection;
    QWidget *leftWidget;

    QVBoxLayout *centerSection;
    QWidget *centerWidget;

    QVBoxLayout *rightSection;
    QWidget *rightWidget;

    QLabel *scoreLabel;
    QList<QLabel *> stars;
    QLabel *gordonLabel;
    QLabel *dishOrTrashLabel;
};

#endif // FINALSCREEN_H
