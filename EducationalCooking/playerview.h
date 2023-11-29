#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>

QT_BEGIN_NAMESPACE
namespace Ui {
class PlayerView;
}
QT_END_NAMESPACE

class PlayerView : public QMainWindow
{
    Q_OBJECT

public:
    PlayerView(QWidget *parent = nullptr);
    ~PlayerView();

public slots:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void updateClickedIngredient(QImage*, int, int);

private:
    Ui::PlayerView *ui;
    QImage clickedIngredient;

signals:
    void didClickOnIngredient(QPoint);
    void dropIngredient(QPoint);
    void updateIngredientPosition(QPoint);
};
#endif // PLAYERVIEW_H
