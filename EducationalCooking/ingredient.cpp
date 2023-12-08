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

std::string Ingredient::GetName() const
{
    return ingredientName;
}

QImage Ingredient::GetImage() const
{
    return currentImage;
}

QRect Ingredient::GetRect()
{
    QRect rectangle = QRect(xLocation, yLocation, currentImage.width(), currentImage.height());
    return rectangle;
}

bool Ingredient::Cut()
{
    if ((cuttable && !cooked) || (ingredientName == "chicken" || ingredientName == "sausage"))
    {
        cut = true;
        currentImage = cutImage;
        return true;
    }
    else
    {
        return false;
    }
}

bool Ingredient::Cooked()
{
    if (cookable)
    {
        cooked = true;
        currentImage = cookedImage;
    }
    return cookable;
}

bool Ingredient::IsCooked() const
{
    return cooked;
}

bool Ingredient::IsCut() const
{
    return cut;
}

bool Ingredient::IsCuttable() const
{
    return cuttable;
}

bool Ingredient::isCookable() const
{
    return cookable;
}

bool Ingredient::operator ==(Ingredient lhs)
{
    if (this->GetName() == lhs.GetName())
        return true;
    return false;
}
