#include "Platform.h"

void Platform::draw(QGraphicsScene *scene) {
    QPixmap platform(":/images/platform");
    platform = platform.scaled(width, height, Qt::KeepAspectRatio);

    width = platform.width();
    setPixmap(platform);
    scene->addItem(this);

    setPos(position.x, position.y);
}

Platform::Platform(QGraphicsScene *scene) {
    width = scene->width();
    height = scene->height() / 7;
}
