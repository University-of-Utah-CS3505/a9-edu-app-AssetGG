#ifndef TOOLS_H
#define TOOLS_H

#include <QImage>
#include <QString>
#include "ingredient.h"

enum class CookingToolType {
    CuttingBoard,
    FryingPan,
    Pot,
    // TODO: Add other tools
};

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

    void ProcessIngredient(Ingredient &ingredient);
};

class CuttingBoard : public Tool
{
public:
    CuttingBoard(int locX, int locY);
};
#endif // TOOLS_H
