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
    // Constructor
    FinalScreen(QWidget *parent = nullptr);

    // Set the score and display the final screen
    void setScore(int score, vector<Ingredient> ingredients, const QString& recipeName);

private:
    // Initialize the layout of the final screen
    void setupLayout();

    // Update the layout based on the score and other parameters
    void updateLayout();

    // Display the dish or trash image based on the score
    void displayDishOrTrash(int score);

    // Display the list of ingredients used in the final dish
    void displayIngredients();

    // Add an ingredient to the list displayed on the final screen
    void addIngredient(const QString &name, const QString &imagePath);

    // Play the audio associated with the final screen
    void playAudio();

    // Vector to store the ingredients used in the final dish
    vector<Ingredient> ingredients;

    // Name of the current recipe
    QString currentRecipeName;

    // Final score
    int score;

    // Layouts and widgets for the different sections of the final screen
    QHBoxLayout *mainLayout;
    QVBoxLayout *leftSection;
    QWidget *leftWidget;
    QVBoxLayout *centerSection;
    QWidget *centerWidget;
    QVBoxLayout *rightSection;
    QWidget *rightWidget;

    // Labels for displaying the score, stars, Gordon Ramsay image, and dish or trash image
    QLabel *scoreLabel;
    QList<QLabel *> stars;
    QLabel *gordonLabel;
    QLabel *dishOrTrashLabel;
};

#endif // FINALSCREEN_H
