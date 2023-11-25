#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include <QPaintEvent>
#include <QObject>
#include <QImage>

using std::vector;

class PlayerCharacter : public QObject
{
    Q_OBJECT
public:
    explicit PlayerCharacter(QObject *parent = nullptr);

public slots:
    void paintEvent(QPaintEvent *);

private:
    vector<QImage> forwardWalkingAnimation;
    vector<QImage> backwardWalkingAnimation;
    vector<QImage> rightWalkingAnimation;
    vector<QImage> leftWalkingAnimation;

signals:

};

#endif // PLAYERCHARACTER_H
