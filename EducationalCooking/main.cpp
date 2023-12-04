#include <QApplication>
#include "controller.h"
#include "physics.h"
#include "playermodel.h"
#include "playerview.h"
#include "startupscreen.h"
#include "comparisoningredient.h"
#include "tools.h"

Recipe testRecipe()
{
    std::vector<ComparisonIngredient> base;
    std::vector<ComparisonIngredient> bonus;
    std::vector<Ingredient> available;

    available.push_back(Ingredient("tomato",
                                   QImage(":/sprites/Sprites/Tomato.png"),
                                   QImage(":/sprites/Sprites/Tomato.png"),
                                   QImage(":/sprites/Sprites/Tomato.png"),
                                   true,
                                   true,
                                   240,
                                   240));
    available.push_back(Ingredient("fishy",
                                   QImage(":/sprites/Sprites/Mackarel.png"),
                                   QImage(":/sprites/Sprites/Mackarel.png"),
                                   QImage(":/sprites/Sprites/Mackarel.png"),
                                   true,
                                   true,
                                   200,
                                   240,
                                   3.0));

    return Recipe("testRecipe", base, bonus, available, QImage());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PlayerView playerView;
    Physics physics;
    PlayerModel model(physics); // Instance of PlayerModel

    Recipe recipe = testRecipe();

    Controller c(model, playerView);

    StartupScreen startupScreen(model, playerView);

    startupScreen.show();

    return a.exec();
}
