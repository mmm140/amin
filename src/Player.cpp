#include "Player.h"
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QApplication>
#include "Platform.h"
#include "Game.h"

void Player::draw(QGraphicsScene *scene) {
    width = scene->width();
    height = scene->height() / 3;
    position = Position(0, 0);
    runTimer = new QTimer(nullptr);
    connect(runTimer, &QTimer::timeout, this, &Player::stopRunAnimate);
    connect(runTimer, &QTimer::timeout, this, &Player::stopRunTimer);

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
    setPixmap(*standRightFrames.at(0));
    scene->addItem(this);

    speed = width;

    heightAnimator = new QPropertyAnimation(this, "Height", this);
    heightAnimator->setStartValue(position.y);
    heightAnimator->setEndValue(position.y);
    heightAnimator->setDuration(1000);
    heightAnimator->start();
    connect(heightAnimator, &QPropertyAnimation::finished, this, &Player::handleGravity);

    widthAnimator = new QPropertyAnimation(this, "Width", this);
    connect(widthAnimator, &QPropertyAnimation::finished, this, &Player::stopRunAnimate);

    setPos(position.x, position.y);
}

Player::~Player() {
    delete SRTimer;
    delete heightAnimator;
    delete widthAnimator;
    delete runTimer;
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
            setPixmap(*standRightFrames.at(++frame));
            break;
        case standLeft:
            if (frame >= 59)
                frame = -1;
            setPixmap(*standLeftFrames.at(++frame));
            break;
        case runRight:
            if (frame >= 29)
                frame = -1;
            setPixmap(*runRightFrames.at(++frame));
            break;
        case runLeft:
            if (frame >= 29)
                frame = -1;
            setPixmap(*runLeftFrames.at(++frame));
            break;
    }

    if (collideGroundEnable)
        collideGround();
    checkGameOver();
    if (collideLeftEnable)
        collideLeftScreen();
    collideUpScreen();
    if (collideRightEnable)
        collideMidScreen();
    fallInHole();
}

void Player::handleGravity() {
    collideGroundEnable = true;
    collideUpEnable = false;
    heightAnimator->stop();
    heightAnimator->setStartValue(y());
    heightAnimator->setEndValue(scene()->height());
    heightAnimator->setDuration(1500);
    heightAnimator->setEasingCurve(QEasingCurve::InQuad);
    heightAnimator->start();
    jumpEnable = true;
}

void Player::handleUpMovement() {
    collideUpEnable = true;
    heightAnimator->stop();
    heightAnimator->setStartValue(y());
    heightAnimator->setEndValue(y() - height);
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
            if (jumpEnable) {
                handleUpMovement();
                collideGroundEnable = false;
            }
            break;
        case Qt::Key::Key_Right:
            if (rightRunEnable) {
                handleRightMovement();
                collideRightEnable = true;
                collideLeftEnable = false;
            } else {
                if (state != runRight) {
                    state = runRight;
                    frame = 0;
                }
                runTimer->stop();
                runTimer->setInterval(500);
                runTimer->start();
            }
            break;
        case Qt::Key::Key_Left:
            if (leftRunEnable) {
                handleLeftMovement();
                collideRightEnable = false;
                collideLeftEnable = true;
            }
            break;
        case Qt::Key::Key_Down:
            if (collideUpEnable)
                handleDownMovement();
            collideGroundEnable = true;
            break;
    }
}

void Player::handleRightMovement() {
    leftRunEnable = true;
    if (state != runRight) {
        state = runRight;
        frame = 0;
    }
    widthAnimator->stop();
    widthAnimator->setStartValue(x());
    widthAnimator->setEndValue(x() + speed);
    widthAnimator->setDuration(500);
    widthAnimator->start();

    runTimer->stop();
    runTimer->setInterval(500);
    runTimer->start();
}

void Player::handleLeftMovement() {
    rightRunEnable = true;
    if (state != runLeft) {
        state = runLeft;
        frame = 0;
    }
    widthAnimator->stop();
    widthAnimator->setStartValue(x());
    widthAnimator->setEndValue(x() - speed);
    widthAnimator->setDuration(500);
    widthAnimator->start();
}

void Player::stopRunAnimate() {
    if (state == runRight)
        state = standRight;
    else if (state == runLeft)
        state = standLeft;
    frame = 0;
}

void Player::handleDownMovement() {
    collideUpEnable = false;
    heightAnimator->stop();
    heightAnimator->setStartValue(y());
    heightAnimator->setEndValue(scene()->height());
    heightAnimator->setDuration(500);
    heightAnimator->setEasingCurve(QEasingCurve::InQuad);
    heightAnimator->start();
    jumpEnable = true;
}

void Player::collideGround() {
    for (QGraphicsItem *Item : collidingItems())
    {
        Platform *platform = dynamic_cast<Platform *>(Item);
        if (platform && platform->y() >= (y() + height - 85))
        {
            heightAnimator->stop();
            heightAnimator->setStartValue(y());
            heightAnimator->setEndValue(platform->y() - height);
            heightAnimator->setDuration(100);
            heightAnimator->setEasingCurve(QEasingCurve::OutQuad);
            heightAnimator->start();
            jumpEnable = true;
            break;
        }
    }
}

void Player::checkGameOver() {
    if (y() >= scene()->height())
        emit gameOver();
}

void Player::collideLeftScreen() {
    if (x() <= 0)
    {
        stopRunAnimate();
        widthAnimator->stop();
        widthAnimator->setStartValue(x());
        widthAnimator->setEndValue(0);
        widthAnimator->setDuration(100);
        widthAnimator->setEasingCurve(QEasingCurve::OutQuad);
        widthAnimator->start();
        leftRunEnable = false;
    }
}

void Player::collideUpScreen() {
    if (y() <= 0 && jumpEnable)
    {
        heightAnimator->stop();
        heightAnimator->setStartValue(y());
        heightAnimator->setEndValue(0);
        heightAnimator->setDuration(50);
        heightAnimator->setEasingCurve(QEasingCurve::OutQuad);
        heightAnimator->start();
        jumpEnable = false;
    }
}

void Player::collideMidScreen() {
    if (x() >= scene()->width() * 2.0 / 5.0)
    {
        widthAnimator->stop();
        rightRunEnable = false;
    }
}

void Player::stopRunTimer() {
    runTimer->stop();
}

void Player::fallInHole() {
    if (y() > scene()->height() * 6.0 / 7 - height + 2)
        jumpEnable = false;
}
