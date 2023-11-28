#include "ingredient.h"
#include <string>
#include <QMouseEvent>

Ingredient::Ingredient(std::string name, QImage baseImage, QImage cutImage, bool cuttable, bool cookable)
{
    ingredientName = name;

    currentImage = baseImage;
    baseImage = baseImage;
    cutImage = cutImage;

    cuttable = cuttable;
    cookable = cookable;

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
    }
    return cookable;
}

void Ingredient::Burned()
{
    burnt = true;
}

