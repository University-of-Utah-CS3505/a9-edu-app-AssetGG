#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QObject>

class Ingredient
{
public:
    Ingredient(QImage, std::string, QImage, bool, bool);
    std::string GetName();
    QImage GetImage();
    bool Cut();
    bool Cooked();

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

};

#endif // INGREDIENT_H
