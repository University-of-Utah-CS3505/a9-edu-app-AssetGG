/*
 * Name: Kazimar Guenther, David Cosby, Caroline Cheng
 * Reviewed By: Nathaniel Taylor
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: Sets up the data necessary to represent the state and appearance of
 * Ingredients in the game.
 */

#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QObject>
#include <QImage>
#include <QPaintEvent>

class Ingredient
{
public:
    Ingredient(std::string, QImage, QImage, QImage, bool, bool, int, int, float scaleFactor = 1.5);
    Ingredient();
    int xLocation, yLocation;

    /// Retrieves the name of the ingredient
    std::string GetName() const;

    /// Retrieves the currently displayed image of the ingredient
    QImage GetImage() const;

    /// Retrieves the bounding rectangle for the currently displayed image of the ingredient
    QRect GetRect();

    /// Uses the names of two ingredients to determine whether two ingredients are equal
    bool operator==(Ingredient);

    /// Getter for cooked property
    bool IsCooked() const;
    /// Getter for cut property
    bool IsCut() const;

    /// Getter for cuttable property
    bool IsCuttable() const;
    /// Getter for cookable property
    bool isCookable() const;

    /// Cuts the ingredient
    bool Cut();
    /// Cooks the ingredient
    bool Cooked();

private:
    std::string ingredientName;

    QImage currentImage;
    QImage baseImage;
    QImage cutImage;
    QImage cookedImage;

    bool cuttable;
    bool cookable;

    bool cut;
    bool cooked;
};

#endif // INGREDIENT_H
