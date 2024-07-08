#include "Platform.h"

void Platform::draw(QGraphicsScene *scene) {
    QPixmap platform(":/images/platform");
    platform = platform.scaled(width, height, Qt::KeepAspectRatio);

    width = platform.width();
    setPixmap(platform);
    scene->addItem(this);

    setPos(position.x, position.y);
    widthAnimator = new QPropertyAnimation(this, "Width", this);
}

Platform::Platform(QGraphicsScene *scene, int speed) {
    this->speed = speed;
    width = scene->width();
    height = scene->height() / 7;
}

Platform::~Platform() {
    delete widthAnimator;
}

void Platform::handle_leftMovement()
{
    widthAnimator->stop();
    widthAnimator->setStartValue(x());
    widthAnimator->setEndValue(x()-speed);
    widthAnimator->setDuration(500);
    widthAnimator->start();
}

void Platform::stopMovement() {
    widthAnimator->stop();
}
