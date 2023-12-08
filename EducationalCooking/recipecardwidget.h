#ifndef RECIPECARDWIDGET_H
#define RECIPECARDWIDGET_H

#include <QWidget>
#include <QImage>
#include <QMouseEvent>

namespace Ui {
class RecipeCardWidget;
}

class RecipeCardWidget : public QWidget
{
    Q_OBJECT

public:
    /// Constructor
    explicit RecipeCardWidget(QWidget *parent = nullptr);

    /// Destructor
    ~RecipeCardWidget();

    /// Set the name of the recipe
    void setRecipeName(const QString &name);

    /// Set the image for the recipe card
    void setRecipeImage(const QString &imagePath);

    /// Get the name of the recipe
    QString getRecipeName();

    /// Check if the recipe card is selected
    bool isSelected() const;

signals:
    /// Signal emitted when the recipe card is clicked
    void clicked();

    /// Signal emitted when a specific recipe is clicked
    void recipeClicked(const QString &recipeName);

protected:
    /// Handle mouse press events on the recipe card
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::RecipeCardWidget *ui;

    /// Flag indicating whether the recipe card is selected
    bool selected;

    /// Method called when the recipe card is clicked
    void onCardClicked();
};

#endif // RECIPECARDWIDGET_H
