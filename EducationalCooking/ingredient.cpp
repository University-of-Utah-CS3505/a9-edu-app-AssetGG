#include "ingredient.h"
#include <string>
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

    locX = x;
    locY = y;

    currentImage = currentImage.scaled(currentImage.width() * scaleFactor,
                                       currentImage.height() * scaleFactor);

    cut = false;
    cooked = false;
    burnt = false;
}

Ingredient::Ingredient()
{
    ingredientName = "tomato";

    currentImage = QImage(":/sprites/Sprites/Tomato.png");
    baseImage = QImage(":/sprites/Sprites/Tomato.png");
    cutImage = QImage(":/sprites/Sprites/Tomato.png");
    cookedImage = QImage(":/sprites/Sprites/Tomato.png");

    cuttable = true;
    cookable = true;

    cut = false;
    cooked = false;
    burnt = false;
}

std::string Ingredient::GetName()
{
    return ingredientName;
}

QImage Ingredient::GetImage()
{
    return currentImage;
}

QRect Ingredient::GetRect()
{
    QRect rectangle = QRect(locX, locY, currentImage.width(), currentImage.height());
    return rectangle;
}

bool Ingredient::Cut()
{
    if (cuttable && !cooked)
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
    if(cookable)
    {
        cooked = true;
        currentImage = cookedImage;
    }
    return cookable;
}

void Ingredient::Burned()
{
    burnt = true;
}

bool Ingredient::IsCooked()
{
    return cooked;
}
bool Ingredient::IsCut()
{
    return cut;
}
bool Ingredient::IsBurned()
{
    return burnt;
}
