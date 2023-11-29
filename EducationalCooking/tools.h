#ifndef TOOLS_H
#define TOOLS_H

#include <QImage>
#include <QString>

enum class CookingToolType
{
    CuttingBoard,
    Pan,
    Pot,
    // TODO: Add other tools
};

class Tools
{
public:
    Tools();
    CookingToolType GetToolType() const;

private:
    CookingToolType toolType;
};

#endif // TOOLS_H
