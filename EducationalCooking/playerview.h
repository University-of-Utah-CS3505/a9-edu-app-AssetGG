#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include "ingredient.h"
#include "physics.h"
#include "recipe.h"
#include "tools.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class PlayerView;
}
QT_END_NAMESPACE

class PlayerView : public QMainWindow
{
    Q_OBJECT
    std::map<std::string, Tool> *tools;
    std::map<std::string, Ingredient> ingredientSprites;

public:
    PlayerView(QWidget *parent = nullptr);
    ~PlayerView();
    void setupScene(Recipe &recipe, std::map<std::string, Tool> &tools);
    void updateSpritePositions(const std::map<std::string, Physics::PhysicsObject> &physicsObjects);

public slots:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::PlayerView *ui;

    Ingredient *getIngredientByName(std::string name);
    Tool *getToolByName(std::string name);

signals:
    void itemGrabbed(std::string itemName, QPoint mousePos);
    void itemDropped(QPoint mousePos);
    void updateDragPosition(QPoint mousePos);
};
#endif // PLAYERVIEW_H
