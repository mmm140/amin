#include "Decorator.h"


void Decorator::draw(QGraphicsScene *scene) {
    QPixmap pixmap(":/images/hills");
    pixmap = pixmap.scaled(width, height, Qt::KeepAspectRatioByExpanding);
	pixmap = pixmap.copy(0,0,520,592);
 	width = pixmap.width();
	setPixmap(pixmap);
	scene->addItem(this);
	setPos(position.x, position.y);
}

Decorator::Decorator(QGraphicsScene *scene) {
    width = scene->width();
    height = scene->height() / 2;
}

void Decorator::stopRunAnimate() {

}


