#include "ingredient.h"
#include <QMouseEvent>

// Constructor of the ingredient object.
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
}

// Default constructor
Ingredient::Ingredient()
{
    // Default constructor has no need to do anything. Only used so
    // ingredients don't have to be set to something in the constructor
}

// Getter for the name of the ingredient.
std::string Ingredient::GetName() const
{
    return ingredientName;
}

// Getter for the current image of the ingredient.
QImage Ingredient::GetImage() const
{
    return currentImage;
}

// Creates a QRect for the current state of the ingredient.
QRect Ingredient::GetRect()
{
    QRect rectangle = QRect(locX, locY, currentImage.width(), currentImage.height());
    return rectangle;
}

// Checks if the ingredient is cuttable. If it is update the currentImage and sets cut to true.
// Returns cuttable.
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

// Checks if the ingredient is cookable. If it is update the currentImage and sets cooked to true.
// Returns cookable.
bool Ingredient::Cooked()
{
    if (cookable)
    {
        cooked = true;
        currentImage = cookedImage;
    }
    return cookable;
}

// Getter for cooked.
bool Ingredient::IsCooked() const
{
    return cooked;
}

// Getter for cut.
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
