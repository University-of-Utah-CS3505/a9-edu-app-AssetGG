#ifndef FINALSCREEN_H
#define FINALSCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class FinalScreen : public QWidget {
    Q_OBJECT

public:
    FinalScreen(QWidget *parent = nullptr);

    void setScore(int score, const QString& recipeName);

private:
    void setupLayout();
    void displayDishOrTrash(int score);
    void displayIngredients();
    void addIngredient(const QString &name, const QString &imagePath);
    QString currentRecipeName;

    QVBoxLayout *leftSection;
    QWidget *leftWidget;

    QVBoxLayout *centerSection;
    QWidget *centerWidget;

    QVBoxLayout *rightSection;
    QWidget *rightWidget;

    QLabel *scoreLabel;
    QList<QLabel *> stars;
    QLabel *gordonLabel;
    QLabel *dishOrTrashLabel;
};

#endif // FINALSCREEN_H
