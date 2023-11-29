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
    explicit RecipeCardWidget(QWidget *parent = nullptr);
    ~RecipeCardWidget();

    void setRecipeName(const QString &name);
    void setRecipeImage(const QString &imagePath);
    QString getRecipeName();
    bool isSelected() const;

signals:
    void clicked();
    void recipeClicked(const QString &recipeName);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::RecipeCardWidget *ui;
    bool selected;
    void onCardClicked();
};

#endif // RECIPECARDWIDGET_H
