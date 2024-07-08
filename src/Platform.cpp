#include "Platform.h"

void Platform::draw(QGraphicsScene *scene) {
    width = scene->width();
    height = scene->height() / 7;
    position = Position(0, scene->height() - height);

    QPixmap sprite(":/images/platform");
    sprite = sprite.scaled(width, height, Qt::KeepAspectRatio);

    width = sprite.width();
    setPixmap(sprite);
    scene->addItem(this);

    setPos(position.x, position.y);
}
