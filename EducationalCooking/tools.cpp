#include "tools.h"
#include <QMouseEvent>

Tool::Tool(std::string name, bool movable, int locX, int locY):
    name(name),
    movable(movable),
    locX(locX),
    locY(locY)
{ }

bool Tool::IsMovable()
{
    return movable;
}

QImage Tool::GetImage()
{
    return baseImage;
}

std::string Tool::GetName()
{
    return name;
}

void Tool::ProcessIngredient(Ingredient &ingredient)
{
    qDebug() << "ProcessIngredient() has not been implemented for " << name;
}

CuttingBoard::CuttingBoard(int locX, int locY)
    : Tool("CuttingBoard", true, locX, locY)
{
    baseImage = QImage(":/sprites/Sprites/CuttingBoard.png");
    baseImage = baseImage.scaled(baseImage.width() * 3.0, baseImage.height() * 3.0);
    currentImage = baseImage;
}

void CuttingBoard::ProcessIngredient(Ingredient &ingredient)
{
    if (ingredient.IsCuttable()) {
        // chicken and sausage needs to be cooked before cut
        if (ingredient.GetName() == "chicken" || ingredient.GetName() == "sausage")
        {
            if (ingredient.IsCooked())
            {
                ingredient.Cut();
            }
        }
        else
        {
            ingredient.Cut();
        }
    }
}

void FryingPan::ProcessIngredient(Ingredient &ingredient)
{
    if (ingredient.isCookable() == true)
    {
        if (ingredient.GetName() == "chicken" || ingredient.GetName() == "dough"
            || ingredient.GetName() == "patty" || ingredient.GetName() == "bun"
            || ingredient.GetName() == "sausage" || ingredient.GetName() == "eggs")
        {
            ingredient.Cooked();
        }
    }
}

void Pot::ProcessIngredient(Ingredient &ingredient)
{
    if (ingredient.isCookable() == true) {
        if (ingredient.GetName() == "noodles" || ingredient.GetName() == "meatballs")
        {
            ingredient.Cooked();
        }
    }
}

FryingPan::FryingPan(int locX, int locY)
    : Tool("FryingPan", true, locX, locY)
{
    baseImage = QImage(":/sprites/Sprites/frying pan.png");
    baseImage = baseImage.scaled(baseImage.width() * 2.5, baseImage.height() * 2.5);
    currentImage = baseImage;
}

Pot::Pot(int locX, int locY)
    : Tool("Pot", true, locX, locY)
{
    baseImage = QImage(":/sprites/Sprites/Pot With Water.png");
    baseImage = baseImage.scaled(baseImage.width() * 3.5, baseImage.height() * 3.5);
    currentImage = baseImage;
}
