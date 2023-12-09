/*
 * Name: Kazimar Guenther, David Cosby, Caroline Cheng
 * Reviewed By: Nathaniel Taylor
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: Holds the information necessary to represent the state and appearance of
 * Ingredients in the game.
 */

#include "ingredient.h"
#include <QMouseEvent>

Ingredient::Ingredient(std::string name,
                       QImage baseImage,
                       QImage cutImage,
                       QImage cookedImage,
                       bool cuttable,
                       bool cookable,
                       int x,
                       int y,
                       float scaleFactor)
    : currentImage(baseImage)
    , baseImage(baseImage)
    , cutImage(cutImage)
    , cookedImage(cookedImage)
    , cuttable(cuttable)
    , cookable(cookable)
{
    ingredientName = name;

    xLocation = x;
    yLocation = y;

    int width = currentImage.width() * scaleFactor;
    int height = currentImage.height() * scaleFactor;

    this->currentImage = currentImage.scaled(width, height);
    this->baseImage = baseImage.scaled(width, height);
    this->cutImage = cutImage.scaled(width, height);
    this->cookedImage = cookedImage.scaled(width, height);

    cut = false;
    cooked = false;
}

Ingredient::Ingredient()
{
    // Default constructor has no need to do anything. Only used so
    // ingredients don't have to be set to something in the constructor
}

std::string Ingredient::getName() const
{
    return ingredientName;
}

QImage Ingredient::getImage() const
{
    return currentImage;
}

QRect Ingredient::getRect()
{
    QRect rectangle = QRect(xLocation, yLocation, currentImage.width(), currentImage.height());
    return rectangle;
}

bool Ingredient::cutIngredient()
{
    if ((cuttable && !cooked) || (ingredientName == "chicken" || ingredientName == "sausage"))
    {
        cut = true;
        currentImage = cutImage;
    }
    return cuttable;
}

bool Ingredient::cookIngredient()
{
    if (cookable)
    {
        cooked = true;
        currentImage = cookedImage;
    }
    return cookable;
}

bool Ingredient::isCooked() const
{
    return cooked;
}

bool Ingredient::isCut() const
{
    return cut;
}

bool Ingredient::isCuttable() const
{
    return cuttable;
}

bool Ingredient::isCookable() const
{
    return cookable;
}

bool Ingredient::operator ==(Ingredient lhs)
{
    if (this->getName() == lhs.getName())
        return true;
    return false;
}
