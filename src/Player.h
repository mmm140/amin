#ifndef AMIN_PLAYER_H
#define AMIN_PLAYER_H

#include "Bodyobject.h"
#include <QList>
#include <QPixmap>
#include <QTimer>

class Player : public Bodyobject {
    Q_OBJECT
private:
    int frame{};
    QList<QPixmap *> frames{};
    QTimer *standTimer{};
    QTimer *runTimer{};

    int speed;
    Position velocity;
public:
    Player();
    ~Player();
    void draw(QGraphicsScene *scene) override;
    void handleGravity();
    void handleRightMovement();
    void handleLeftMovement();
    void handleUpMovement();
    void handleDownMovement();
    void handleMovement();
public slots:
    void standRightAnimate();
};

#endif //AMIN_PLAYER_H
