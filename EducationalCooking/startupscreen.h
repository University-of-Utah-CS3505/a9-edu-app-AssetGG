#ifndef STARTUPSCREEN_H
#define STARTUPSCREEN_H

#include <QWidget>
#include "playermodel.h"
#include "playerview.h"
#include "recipecardwidget.h"

namespace Ui {
class StartupScreen;
}

class StartupScreen : public QWidget {
    Q_OBJECT

public:
    StartupScreen(PlayerModel &model, PlayerView &view, QWidget *parent = nullptr);
    ~StartupScreen();

private slots:
    void onRecipeCardClicked(int recipeIndex);
    void handleRecipeCardClicked(const QString &recipeName);
    void onLearnRecipeClicked();

private:
    QVector<RecipeCardWidget*> recipeCards;
    Ui::StartupScreen *ui;
    PlayerModel& playerModel;
    PlayerView &playerView;

    QImage recipeCardImage1;
    QImage recipeCardImage2;
    QImage recipeCardImage3;
    QImage recipeCardImage4;
    QImage recipeCardImage5;
    QImage recipeCardImage6;

    void createRecipeCards();
    void updateRecipeCard(RecipeCardWidget* card, const QString& recipeName);
    void updateRecipeCardImage(RecipeCardWidget* card, const QString& imagePath);
};

#endif // STARTUPSCREEN_H
