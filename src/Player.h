#ifndef AMIN_PLAYER_H
#define AMIN_PLAYER_H

#include "Bodyobject.h"
#include <QList>
#include <QPixmap>
#include <QTimer>
#include <QPropertyAnimation>

class Player : public Bodyobject {
    Q_OBJECT
    Q_PROPERTY(qreal height READ Bodyobject::y WRITE Bodyobject::setY)
private:
    int frame{};
    QList<QPixmap *> frames{};
    QTimer *standTimer{};
    QTimer *runTimer{};
    QPropertyAnimation *heightAnimator{};
    int groundY{};
    int speed;
    Position velocity;
public:
    Player();
    ~Player();
    void draw(QGraphicsScene *scene) override;
    void handleRightMovement();
    void handleLeftMovement();
    void handleUpMovement();
    void handleDownMovement();
    void handleMovement();
public slots:
    void standRightAnimate();
    void handleGravity();
};

#endif //AMIN_PLAYER_H
