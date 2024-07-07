#include "Player.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

Player::Player() : Bodyobject(40, 100, Position(0, 0)), velocity(10, 0) {
    speed = 10;
}

void Player::draw(QGraphicsScene *scene) {

}

Player::~Player() {
    delete image;
}