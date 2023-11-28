#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include "playermodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PlayerView; }
QT_END_NAMESPACE

class PlayerView : public QMainWindow
{
    Q_OBJECT

public:
    PlayerView(PlayerModel& model, QWidget *parent = nullptr);
    ~PlayerView();

public slots:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    Ui::PlayerView *ui;

signals:
    void didClickOnIngredient(QPoint);
    void unclickIngredient(QPoint);
    void updateIngredientPosition(QPoint);

};
#endif // PLAYERVIEW_H
