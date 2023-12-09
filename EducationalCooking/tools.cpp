/*
 * Name: Asset Yerzhigit, Caroline Cheng, David Cosby
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: Contains a base Tool class and other tools extending
 * from that (CuttingBoard, Pot, Pan) to define cooking tools in our game.
 * Provides basic tool data and logic for how each tool should process
 * ingredients.
 * Reviewed By: David Cosby
 */

#include "tools.h"
#include <QMouseEvent>

Tool::Tool(std::string name, bool movable, int locX, int locY):
    name(name),
    movable(movable),
    xLocation(locX),
    yLocation(locY)
{

}

bool Tool::isMovable()
{
    return movable;
}

QImage Tool::getImage()
{
    return baseImage;
}

std::string Tool::getName()
{
    return name;
}

void Tool::processIngredient(Ingredient &)
{
    // Implementation handled by children
}

CuttingBoard::CuttingBoard(int locX, int locY)
    : Tool("CuttingBoard", true, locX, locY)
{
    baseImage = QImage(":/sprites/Sprites/CuttingBoard.png");
    baseImage = baseImage.scaled(baseImage.width() * 3.0, baseImage.height() * 3.0);
    currentImage = baseImage;
}

void CuttingBoard::processIngredient(Ingredient &ingredient)
{
    if (ingredient.isCuttable())
    {
        // chicken and sausage needs to be cooked before cut
        if (ingredient.getName() == "chicken" || ingredient.getName() == "sausage")
            if (ingredient.isCooked())
                ingredient.cutIngredient();
        else
            ingredient.cutIngredient();
    }
}

void FryingPan::processIngredient(Ingredient &ingredient)
{
    if (ingredient.isCookable() == true)
    {
        if (ingredient.getName() == "chicken" || ingredient.getName() == "dough"
            || ingredient.getName() == "patty" || ingredient.getName() == "bun"
            || ingredient.getName() == "sausage" || ingredient.getName() == "eggs")
            ingredient.cookIngredient();
    }
}

void Pot::processIngredient(Ingredient &ingredient)
{
    if (ingredient.isCookable() == true)
        if (ingredient.getName() == "noodles" || ingredient.getName() == "meatballs")
            ingredient.cookIngredient();
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
