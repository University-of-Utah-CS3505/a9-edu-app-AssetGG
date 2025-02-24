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
/*
 * Name: Kazimar Guenther, David Cosby, Caroline Cheng
 * Reviewed By: Nathaniel Taylor
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: Sets up the information necessary to represent the state and appearance of
 * Ingredients in the game.
 */

#include <QImage>
#include <QPaintEvent>

class Ingredient
{
public:

    /// Creates an ingredient object from the given name with the given current image, cut image, and cooked image
    /// (all images are made with the given width and height and scaled by the scaleFactor).
    /// It also sets the cuttable and cookable properties
    Ingredient(std::string, QImage, QImage, QImage, bool, bool, int, int, float scaleFactor = 1.5);
    Ingredient();
    int xLocation, yLocation;

    /// Retrieves the name of the ingredient
    std::string getName() const;

    /// Retrieves the currently displayed image of the ingredient
    QImage getImage() const;

    /// Retrieves the bounding rectangle for the currently displayed image of the ingredient
    QRect getRect();

    /// Uses the names of two ingredients to determine whether two ingredients are equal
    bool operator==(Ingredient);

    /// Getter for cooked property
    bool isCooked() const;

    /// Getter for cut property
    bool isCut() const;

    /// Getter for cuttable property
    bool isCuttable() const;

    /// Getter for cookable property
    bool isCookable() const;

    /// Cuts the ingredient
    bool cutIngredient();

    /// Cooks the ingredient
    bool cookIngredient();

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
