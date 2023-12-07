/*
 * Name: Kazimar Guenther, David Cosby,
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

    bool IsCooked() const;
    bool IsCut() const;
    bool IsBurned() const;

    bool IsCuttable() const;

    bool Cut();
    bool Cooked();
    void Burned();

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
    bool dirty;
    bool burnt;
};

#endif // INGREDIENT_H
