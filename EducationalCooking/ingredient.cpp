#include "ingredient.h"
#include <string>

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
}

std::string Ingredient::GetName()
{
    return name;
}

QImage Ingredient::GetImage()
{
    return currentImage;
}

void Ingredient::Cut()
{
    if (cuttable)
    {
        cut = true;
        currentImage = cutImage;
    }
}

void Ingredient::Cooked()
{
    if(cookable)
    {
        cooked = true;
    }
}


