#include "Player.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

Player::Player() : velocity(10, 0) {
    speed = 10;
}

void Player::draw(QGraphicsScene *scene) {
    width = scene->width();
    height = scene->height() / 3;
    position = Position(0, 0);
    groundY = scene->height();

    image = new QGraphicsPixmapItem(nullptr);

    for (int i = 0; i < 60; ++i) {
        QPixmap sprite(":/images/SStandR");
        sprite = sprite.scaled(width, height, Qt::KeepAspectRatioByExpanding);
        auto *frm = new QPixmap;
        *frm = sprite.copy(i * sprite.width() / 60, 0, sprite.width() / 60, sprite.height());
        frames.append(frm);
    }

    standTimer = new QTimer();
    standTimer->setInterval(40);
    connect(standTimer, &QTimer::timeout, this, &Player::standRightAnimate);
    standTimer->start();

    image->setPixmap(*frames.at(0));
    scene->addItem(image);

    heightAnimator = new QPropertyAnimation(this, "Height", this);
    heightAnimator->setStartValue(position.y);
    heightAnimator->setEndValue(position.y);
    heightAnimator->setDuration(2000);
    heightAnimator->start();
    connect(heightAnimator, &QPropertyAnimation::finished, this, &Player::handleGravity);

    image->setPos(position.x, position.y);
}

Player::~Player() {
    delete image;
    qDeleteAll(frames);
}

void Player::standRightAnimate() {
    if (frame >= 59)
        frame = -1;
    image->setPixmap(*frames.at(++frame));
}

void Player::handleGravity() {
    heightAnimator->stop();
    heightAnimator->setStartValue(image->y());
    heightAnimator->setEndValue(groundY);
    heightAnimator->setDuration(1000);
    heightAnimator->start();
}
