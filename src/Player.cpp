#include "Player.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QApplication>

Player::Player() : velocity(10, 0) {
    speed = 10;
}

void Player::draw(QGraphicsScene *scene) {
    width = scene->width();
    height = scene->height() / 3;
    position = Position(0, 0);
    sceneHeight = scene->height();

    image = new QGraphicsPixmapItem(nullptr);
//    image->setFlags(QGraphicsItem::ItemIsFocusable);
//    image->setFocus();

    for (int i = 0; i < 60; ++i) {
        QPixmap sprite(":/images/SStandR");
        sprite = sprite.scaled(width, height, Qt::KeepAspectRatioByExpanding);
        auto *frm = new QPixmap;
        *frm = sprite.copy(i * sprite.width() / 60, 0, sprite.width() / 60, sprite.height());
        standRightFrames.append(frm);
    }

    for (int i = 0; i < 60; ++i) {
        QPixmap sprite(":/images/SStandL");
        sprite = sprite.scaled(width, height, Qt::KeepAspectRatioByExpanding);
        auto *frm = new QPixmap;
        *frm = sprite.copy(i * sprite.width() / 60, 0, sprite.width() / 60, sprite.height());
        standLeftFrames.append(frm);
    }

    for (int i = 0; i < 30; ++i) {
        QPixmap sprite(":/images/SRunR");
        sprite = sprite.scaled(width, height, Qt::KeepAspectRatioByExpanding);
        auto *frm = new QPixmap;
        *frm = sprite.copy(i * sprite.width() / 30, 0, sprite.width() / 30, sprite.height());
        runRightFrames.append(frm);
    }

    for (int i = 0; i < 30; ++i) {
        QPixmap sprite(":/images/SRunL");
        sprite = sprite.scaled(width, height, Qt::KeepAspectRatioByExpanding);
        auto *frm = new QPixmap;
        *frm = sprite.copy(i * sprite.width() / 30, 0, sprite.width() / 30, sprite.height());
        runLeftFrames.append(frm);
    }

    standTimer = new QTimer();
    standTimer->setInterval(40);
    connect(standTimer, &QTimer::timeout, this, &Player::standRightAnimate);
    standTimer->start();

    image->setPixmap(*standRightFrames.at(0));
    scene->addItem(image);

    heightAnimator = new QPropertyAnimation(this, "Height", this);
    heightAnimator->setStartValue(position.y);
    heightAnimator->setEndValue(position.y);
    heightAnimator->setDuration(1000);
    heightAnimator->start();
    connect(heightAnimator, &QPropertyAnimation::finished, this, &Player::handleGravity);

    image->setPos(position.x, position.y);
}

Player::~Player() {
    delete image;
    qDeleteAll(standRightFrames);
}

void Player::standRightAnimate() {
    if (frame >= 59)
        frame = -1;
    image->setPixmap(*standRightFrames.at(++frame));
}

void Player::handleGravity() {
    heightAnimator->stop();
    heightAnimator->setStartValue(image->y());
    heightAnimator->setEndValue(sceneHeight);
    heightAnimator->setDuration(1500);
    heightAnimator->setEasingCurve(QEasingCurve::InQuad);
    heightAnimator->start();
}

void Player::handleUpMovement() {
    heightAnimator->stop();
    heightAnimator->setStartValue(image->y());
    heightAnimator->setEndValue(image->y() - height);
    heightAnimator->setDuration(700);
    heightAnimator->setEasingCurve(QEasingCurve::OutQuad);
    heightAnimator->start();
}

bool Player::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::KeyPress)
    {
        handleMovement(dynamic_cast<QKeyEvent*>(event));
        return true;
    }
    return Bodyobject::eventFilter(watched, event);
}

void Player::handleMovement(QKeyEvent *keyEvent) {
    switch (keyEvent->key()) {
        case Qt::Key::Key_Up:
            handleUpMovement();
            break;
    }
}


