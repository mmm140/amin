#include "Player.h"
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QApplication>
#include "Platform.h"
#include "Game.h"

void Player::draw(QGraphicsScene *scene) {
    width = scene->width();
    height = scene->height() / 3;
    position = Position(682, 0);
    sceneHeight = scene->height();

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

    speed = width * 2;

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
}

void Player::handleGravity() {
    collideGroundEnable = true;
    heightAnimator->stop();
    heightAnimator->setStartValue(y());
    heightAnimator->setEndValue(sceneHeight);
    heightAnimator->setDuration(1500);
    heightAnimator->setEasingCurve(QEasingCurve::InQuad);
    heightAnimator->start();
}

void Player::handleUpMovement() {
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
            handleUpMovement();
            collideGroundEnable = false;
            break;
        case Qt::Key::Key_Right:
            handleRightMovement();
            break;
        case Qt::Key::Key_Left:
            handleLeftMovement();
            break;
        case Qt::Key::Key_Down:
            handleDownMovement();
            collideGroundEnable = true;
            break;
    }
}

void Player::handleRightMovement() {
    state = runRight;
    widthAnimator->stop();
    widthAnimator->setStartValue(x());
    widthAnimator->setEndValue(x() + speed);
    widthAnimator->setDuration(700);
    widthAnimator->start();
}

void Player::handleLeftMovement() {
    state = runLeft;
    widthAnimator->stop();
    widthAnimator->setStartValue(x());
    widthAnimator->setEndValue(x() - speed);
    widthAnimator->setDuration(700);
    widthAnimator->start();
}

void Player::stopRunAnimate() {
    if (state == runRight)
        state = standRight;
    else if (state == runLeft)
        state = standLeft;
}

void Player::handleDownMovement() {
    heightAnimator->stop();
    heightAnimator->setStartValue(y());
    heightAnimator->setEndValue(sceneHeight);
    heightAnimator->setDuration(500);
    heightAnimator->setEasingCurve(QEasingCurve::InQuad);
    heightAnimator->start();
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
            break;
        }
    }
}

void Player::checkGameOver() {
    if (y() >= scene()->height())
        emit gameOver();
}
