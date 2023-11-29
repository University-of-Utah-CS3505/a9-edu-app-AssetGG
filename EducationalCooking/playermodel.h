#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <QObject>
#include <QPoint>
#include "ingredient.h"

using std::vector;

class PlayerModel : public QObject
{
    Q_OBJECT
public:
    explicit PlayerModel(QObject *parent = nullptr);

public slots:
    void didClickOnIngredient(QPoint);
    void dropIngredient(QPoint);
    void moveIngredientToPoint(QPoint);

private:
    vector<Ingredient> ingredients;
    Ingredient* currentlyClickedOn;


signals:
    void updateIngredientOnScreen(QImage*, int, int);

};

#endif // PLAYERMODEL_H
