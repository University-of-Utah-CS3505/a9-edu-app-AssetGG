#include "tools.h"
#include <QMouseEvent>
#include <string>

Tool::Tool(std::string name, bool movable, int locX, int locY)
    : name(name)
    , movable(movable)
    , locX(locX)
    , locY(locY)
{
    // Empty constructor
    // Might need to rethink this
}

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

bool Tool::isOverlapping(Ingredient& ingredient)
{
    QRect toolRect(locX, locY, baseImage.width(), baseImage.height());
    QRect ingredientRect(ingredient.GetRect());

    return toolRect.intersects(ingredientRect);
}

CuttingBoard::CuttingBoard(int locX, int locY)
    : Tool("CuttingBoard", true, locX, locY)
{
    baseImage = QImage(":/sprites/Sprites/CuttingBoard.png");
    baseImage = baseImage.scaled(baseImage.width() * 3.0, baseImage.height() * 3.0);
    currentImage = baseImage;
    currentImage = baseImage;
}

FryingPan::FryingPan(int locX, int locY)
    : Tool("FryingPan", true, locX, locY)
{
    // Could not find the sprite for pan
    baseImage = QImage(":/sprites/Sprites/Dorito.png");
    baseImage = baseImage.scaled(baseImage.width() * 3.0, baseImage.height() * 3.0);
    currentImage = baseImage;
    currentImage = baseImage;
}

Pot::Pot(int locX, int locY)
    : Tool("Pot", true, locX, locY)
{
    // Could not find the sprite for pan
    baseImage = QImage(":/sprites/Sprites/Black Olive.png");
    baseImage = baseImage.scaled(baseImage.width() * 3.0, baseImage.height() * 3.0);
    currentImage = baseImage;
    currentImage = baseImage;
}
