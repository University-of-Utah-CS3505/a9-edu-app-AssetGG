#ifndef STARTUPSCREEN_H
#define STARTUPSCREEN_H

#include <QWidget>
#include "playermodel.h"
#include "recipecardwidget.h"

namespace Ui {
class StartupScreen;
}

class StartupScreen : public QWidget {
    Q_OBJECT

public:
    StartupScreen(PlayerModel& model, QWidget *parent = nullptr);
    ~StartupScreen();

private slots:
    void onRecipeCardClicked(int recipeIndex);
    void onLearnRecipeClicked();

private:
    Ui::StartupScreen *ui;
    PlayerModel& playerModel;

    void createRecipeCards();
};

#endif // STARTUPSCREEN_H
