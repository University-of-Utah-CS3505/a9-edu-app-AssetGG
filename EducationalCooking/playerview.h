#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include "ingredient.h"
#include "physics.h"
#include "recipe.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class PlayerView;
}
QT_END_NAMESPACE

class PlayerView : public QMainWindow
{
    Q_OBJECT

public:
    std::map<std::string, Ingredient> ingredientSprites;
    Ingredient tomato;

    PlayerView(QWidget *parent = nullptr);
    ~PlayerView();
    void setupScene(Recipe &recipe);
    void updateSpritePositions(const std::map<std::string, Physics::PhysicsObject> &physicsObjects);

public slots:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::PlayerView *ui;

    Ingredient *getSpriteByName(std::string name);

signals:
    void ingredientGrabbed(std::string ingredientName, QPoint mousePos);
    void ingredientDropped(QPoint mousePos);
    void updateIngredientPosition(QPoint mousePos);
};
#endif // PLAYERVIEW_H
