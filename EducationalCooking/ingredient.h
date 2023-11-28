#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QObject>
#include <QImage>
#include <QPaintEvent>

class Ingredient
{
public:
    Ingredient(std::string, QImage, QImage, bool, bool);
    int x, y;
    std::string GetName();
    QImage GetImage();
    bool Cut();
    bool Cooked();
    void Burned();

private:
    std::string ingredientName;

    QImage currentImage;
    QImage baseImage;
    QImage cutImage;

    bool cuttable;
    bool cookable;

    bool cut;
    bool cooked;
    bool dirty;
    bool burnt;
};

#endif // INGREDIENT_H
