#ifndef TOOLS_H
#define TOOLS_H

#include <QImage>
#include <QString>
#include "ingredient.h"

class Tool
{
    std::string name;
    bool movable;

protected:
    QImage currentImage;
    QImage baseImage;
    QImage inUseImage;

public:
    int locX;
    int locY;

    Tool(std::string name, bool movable, int locX, int locY);

    bool IsMovable();
    QImage GetImage();
    std::string GetName();

    virtual void ProcessIngredient(Ingredient &ingredient);

    bool isOverlapping(Ingredient &ingredient);
};

class CuttingBoard : public Tool
{
public:
    CuttingBoard(int locX, int locY);
    void ProcessIngredient(Ingredient &ingredient);
};

class FryingPan : public Tool
{
public:
    FryingPan(int locX, int locY);
};

class Pot : public Tool
{
public:
    Pot(int locX, int locY);
};
#endif // TOOLS_H
