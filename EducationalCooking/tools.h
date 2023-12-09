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
    int xLocation;
    int yLocation;

    /// Builds a Tool object with the given name and sets the moveable property.
    /// All Tool images are made with the given width and height
    Tool(std::string, bool, int, int);

    /// Returns true if the tool is intended to move or not.
    bool IsMovable();

    /// Returns the tool's sprite
    QImage GetImage();

    /// Returns the tool's name.
    std::string GetName();

    /// Whatever should happen to an ingredient when it is
    /// dropped on this tool.
    virtual void ProcessIngredient(Ingredient&);
};

class CuttingBoard : public Tool
{
public:

    /// Creates a CuttingBoard tool at (locX, locY)
    CuttingBoard(int locX, int locY);

    /// Cuts the ingredient if it is cuttable.
    void ProcessIngredient(Ingredient&);
};

class FryingPan : public Tool
{
public:

    /// Creates a FryingPan tool at (locX, locY)
    FryingPan(int locX, int locY);

    /// Cooks certain ingredients
    void ProcessIngredient(Ingredient&);
};

class Pot : public Tool
{
public:

    /// Creates a Pot tool at (locX, locY)
    Pot(int locX, int locY);

    /// Cooks certain ingredients
    void ProcessIngredient(Ingredient&);
};
#endif // TOOLS_H
