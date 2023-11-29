#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QObject>
#include <QPaintEvent>

class Ingredient
{
public:
    Ingredient();
    int x, y;
    QImage* ingredientImage;

public slots:
};

#endif // INGREDIENT_H
