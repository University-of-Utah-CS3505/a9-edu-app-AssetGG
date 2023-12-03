#ifndef FINALSCREEN_H
#define FINALSCREEN_H

#include <QWidget>

namespace Ui {
class FinalScreen;
}

class FinalScreen : public QWidget
{
    Q_OBJECT

public:
    explicit FinalScreen(QWidget *parent = nullptr);
    ~FinalScreen();

private:
    Ui::FinalScreen *ui;
};

#endif // FINALSCREEN_H
