/*
 * Name: Yukon Zipperer
 * Reviewed By: Caroline Cheng
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: This class displays the final score, ingredients, and food.
 */

#ifndef FINALSCREEN_H
#define FINALSCREEN_H

#include "ingredient.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

using std::vector;

class FinalScreen : public QWidget
{
    Q_OBJECT

public:
    FinalScreen(QWidget *parent = nullptr);

    /// Set the score and display the final screen
    void setScore(int, vector<Ingredient>, const QString&);

private:
    /// Initialize the layout of the final screen
    void setupLayout();

    /// Update the layout based on the score and other parameters
    void updateLayout();

    /// Display the dish or trash image based on the score
    void displayDishOrTrash(int);

    /// Display the list of ingredients used in the final dish
    void displayIngredients();

    /// Add an ingredient to the list displayed on the final screen
    void addIngredient(const QString&, const QString&);

    /// Vector to store the ingredients used in the final dish
    vector<Ingredient> ingredients;

    /// Name of the current recipe
    QString currentRecipeName;

    /// Final score
    int score;

    /// Layouts and widgets for the different sections of the final screen
    QHBoxLayout *mainLayout;
    QVBoxLayout *leftSection;
    QWidget *leftWidget;
    QVBoxLayout *centerSection;
    QWidget *centerWidget;
    QVBoxLayout *rightSection;
    QWidget *rightWidget;

    /// Labels for displaying the score, stars, Gordon Ramsay image, and dish or trash image
    QLabel *scoreLabel;
    QList<QLabel*> stars;
    QLabel *gordonLabel;
    QLabel *dishOrTrashLabel;
};

#endif // FINALSCREEN_H
