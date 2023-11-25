#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <QMainWindow>
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

private:
    Ui::PlayerView *ui;

signals:

};
#endif // PLAYERVIEW_H
