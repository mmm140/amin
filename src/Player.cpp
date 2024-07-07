#include "Player.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

Player::Player() : Bodyobject(40, 100, Position(0, 0)), velocity(10, 0) {
    speed = 10;
}

void Player::draw(QGraphicsScene *scene) {
    image = new QGraphicsPixmapItem(nullptr);

    for (int i = 0; i < 60; ++i) {
        QPixmap sprite(":/images/SStandR");
        sprite = sprite.scaled(scene->width(), scene->height() / 3, Qt::KeepAspectRatioByExpanding);
        QPixmap *frame = new QPixmap;
        *frame = sprite.copy(i * sprite.width() / 60, 0, sprite.width() / 60, sprite.height());
        frames.append(frame);
    }

    standTimer = new QTimer();
    standTimer->setInterval(40);
    connect(standTimer, &QTimer::timeout, this, &Player::standRightAnimate);
    standTimer->start();


    image->setPixmap(*frames.at(0));
    scene->addItem(image);
    image->setPos(0,0);
}

Player::~Player() {
    delete image;

}

void Player::standRightAnimate() {
    if (frame >= 59)
        frame = -1;
    image->setPixmap(*frames.at(++frame));
}
