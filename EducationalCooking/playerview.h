#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class PlayerView; }
QT_END_NAMESPACE

class PlayerView : public QMainWindow
{
    Q_OBJECT

public:
    PlayerView(QWidget *parent = nullptr);
    ~PlayerView();

private:
    Ui::PlayerView *ui;
};
#endif // PLAYERVIEW_H
