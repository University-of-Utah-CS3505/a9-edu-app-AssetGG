/*
 * Name: Kazimar Guenther, David Cosby, Caroline Cheng
 * Class: CS 3505
 * Assignment Name: A9: Edu App
 * Description: Ingredient class to represent the state and appearance of
 *      Ingredients in the game.
 */

#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QObject>
#include <QImage>
#include <QPaintEvent>

class Ingredient
{
public:
    Ingredient(std::string, QImage, QImage, QImage, bool, bool, int, int, float scaleFactor = 1.5);
    Ingredient();
    int locX, locY;
    std::string GetName() const;
    QImage GetImage() const;
    QRect GetRect();
    bool operator==(Ingredient);

    /// Getter for cooked property
    bool IsCooked() const;
    /// Getter for cut property
    bool IsCut() const;

    /// Getter for cuttable property
    bool IsCuttable() const;
    /// Getter for cookable property
    bool isCookable() const;

    /// Cuts the ingredient
    bool Cut();
    /// Cooks the ingredient
    bool Cooked();

private:
    std::string ingredientName;

    QImage currentImage;
    QImage baseImage;
    QImage cutImage;
    QImage cookedImage;

    bool cuttable;
    bool cookable;

    bool cut;
    bool cooked;
};

#endif // INGREDIENT_H
