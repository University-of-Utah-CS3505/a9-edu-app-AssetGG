#ifndef RECIPECARDWIDGET_H
#define RECIPECARDWIDGET_H

#include <QWidget>

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
    bool isSelected() const;

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::RecipeCardWidget *ui;
    bool selected;
};

#endif // RECIPECARDWIDGET_H
