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

    {
        QPixmap sprite(":/images/SStandR");
        sprite = sprite.scaled(width, height, Qt::KeepAspectRatioByExpanding);
        for (int i = 0; i < 60; ++i) {
            auto *frm = new QPixmap;
            *frm = sprite.copy(i * sprite.width() / 60, 0, sprite.width() / 60, sprite.height());
            standRightFrames.append(frm);
        }
    }

    {
        QPixmap sprite(":/images/SStandL");
        sprite = sprite.scaled(width, height, Qt::KeepAspectRatioByExpanding);
        for (int i = 0; i < 60; ++i) {
            auto *frm = new QPixmap;
            *frm = sprite.copy(i * sprite.width() / 60, 0, sprite.width() / 60, sprite.height());
            standLeftFrames.append(frm);
        }
    }

    {
        QPixmap sprite(":/images/SRunR");
        sprite = sprite.scaled(width, height, Qt::KeepAspectRatioByExpanding);
        for (int i = 0; i < 30; ++i) {
            auto *frm = new QPixmap;
            *frm = sprite.copy(i * sprite.width() / 30, 0, sprite.width() / 30, sprite.height());
            runRightFrames.append(frm);
        }
    }

    {
        QPixmap sprite(":/images/SRunL");
        sprite = sprite.scaled(width, height, Qt::KeepAspectRatioByExpanding);
        for (int i = 0; i < 30; ++i) {
            auto *frm = new QPixmap;
            *frm = sprite.copy(i * sprite.width() / 30, 0, sprite.width() / 30, sprite.height());
            runLeftFrames.append(frm);
        }
    }

    SRTimer = new QTimer();
    SRTimer->setInterval(40);
    connect(SRTimer, &QTimer::timeout, this, &Player::animate);
    SRTimer->start();

    width = standRightFrames.at(0)->width();
    image->setPixmap(*standRightFrames.at(0));
    scene->addItem(image);

    heightAnimator = new QPropertyAnimation(this, "Height", this);
    heightAnimator->setStartValue(position.y);
    heightAnimator->setEndValue(position.y);
    heightAnimator->setDuration(1000);
    heightAnimator->start();
    connect(heightAnimator, &QPropertyAnimation::finished, this, &Player::handleGravity);

    widthAnimator = new QPropertyAnimation(this, "Width", this);
    connect(widthAnimator, &QPropertyAnimation::finished, this, &Player::stopRunAnimate);

    image->setPos(position.x, position.y);
}

Player::~Player() {
    delete image;
    delete SRTimer;
    delete heightAnimator;
    delete widthAnimator;
    qDeleteAll(standRightFrames);
    qDeleteAll(standLeftFrames);
    qDeleteAll(runRightFrames);
    qDeleteAll(runLeftFrames);
}

void Player::animate() {
    switch (state) {
        case standRight:
            if (frame >= 59)
                frame = -1;
            image->setPixmap(*standRightFrames.at(++frame));
            break;
        case standLeft:
            if (frame >= 59)
                frame = -1;
            image->setPixmap(*standLeftFrames.at(++frame));
            break;
        case runRight:
            if (frame >= 29)
                frame = -1;
            image->setPixmap(*runRightFrames.at(++frame));
            break;
        case runLeft:
            if (frame >= 29)
                frame = -1;
            image->setPixmap(*runLeftFrames.at(++frame));
            break;
    }
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
        case Qt::Key::Key_Right:
            handleRightMovement();
            break;
        case Qt::Key::Key_Left:
            handleLeftMovement();
            break;
    }
}

void Player::handleRightMovement() {
    state = runRight;
    widthAnimator->stop();
    widthAnimator->setStartValue(image->x());
    widthAnimator->setEndValue(image->x() + 2 * width);
    widthAnimator->setDuration(700);
    widthAnimator->start();
}

void Player::handleLeftMovement() {
    state = runLeft;
    widthAnimator->stop();
    widthAnimator->setStartValue(image->x());
    widthAnimator->setEndValue(image->x() - 2 * width);
    widthAnimator->setDuration(700);
    widthAnimator->start();
}

void Player::stopRunAnimate() {
    if (state == runRight)
        state = standRight;
    else if (state == runLeft)
        state = standLeft;
}


