#include <QApplication>
#include "controller.h"
#include "physics.h"
#include "playermodel.h"
#include "playerview.h"
#include "startupscreen.h"

Recipe testRecipe()
{
    std::vector<Ingredient> base;
    std::vector<Ingredient> bonus;
    std::vector<Ingredient> available;

    available.push_back(Ingredient("tomato",
                                   QImage(":/sprites/Sprites/Tomato.png"),
                                   QImage(":/sprites/Sprites/Tomato.png"),
                                   QImage(":/sprites/Sprites/Tomato.png"),
                                   true,
                                   true,
                                   240,
                                   240));
    available.push_back(Ingredient("tomato2",
                                   QImage(":/sprites/Sprites/Tomato.png"),
                                   QImage(":/sprites/Sprites/Tomato.png"),
                                   QImage(":/sprites/Sprites/Tomato.png"),
                                   true,
                                   true,
                                   200,
                                   240));

    return Recipe("testRecipe", base, bonus, available);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PlayerView playerView;
    Physics physics;
    PlayerModel model(physics); // Instance of PlayerModel

    Recipe recipe = testRecipe();
    model.setupScene(recipe);
    playerView.setUpScene(recipe);

    Controller c(model, playerView);

    StartupScreen startupScreen(model, playerView);

    startupScreen.show();

    return a.exec();
}
