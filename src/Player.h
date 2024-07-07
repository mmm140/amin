#ifndef AMIN_PLAYER_H
#define AMIN_PLAYER_H

#include "Bodyobject.h"

class Player : public Bodyobject {
private:
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
};

#endif //AMIN_PLAYER_H
