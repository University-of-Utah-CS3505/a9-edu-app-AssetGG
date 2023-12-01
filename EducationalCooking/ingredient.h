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
    std::string GetName();
    QImage GetImage();
    QRect GetRect();
    bool IsCooked();
    bool IsCut();
    bool IsBurned();
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
