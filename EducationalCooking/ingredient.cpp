#include "ingredient.h"
#include <QMouseEvent>
#include <string>

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

    int w = currentImage.width() * scaleFactor;
    int h = currentImage.height() * scaleFactor;

    this->currentImage = currentImage.scaled(w, h);
    this->baseImage = baseImage.scaled(w, h);
    this->cutImage = cutImage.scaled(w, h);
    this->cookedImage = cookedImage.scaled(w, h);

    cut = false;
    cooked = false;
    burnt = false;
}

std::string Ingredient::GetName() const
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
    if (cuttable && !cooked) {
        cut = true;
        currentImage = cutImage;
        return true;
    } else {
        return false;
    }
}

bool Ingredient::Cooked()
{
    if (cookable) {
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

bool Ingredient::IsCuttable()
{
    return cuttable;
}

bool Ingredient::IsBurned()
{
    return burnt;
}
