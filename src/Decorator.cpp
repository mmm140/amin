#include "Decorator.h"


void Decorator::draw(QGraphicsScene *scene) {
    QPixmap pixmap(":/images/hills");
    pixmap = pixmap.scaled(width, height, Qt::KeepAspectRatioByExpanding);
	pixmap = pixmap.copy(0,0,520,592);
 	width = pixmap.width();
	setPixmap(pixmap);
	scene->addItem(this);
	setPos(position.x, position.y);
	widthAnimator = new QPropertyAnimation(this, "Width", this);
}

Decorator::Decorator(QGraphicsScene *scene, int speed) {
    flag = true;
	this->speed=speed;
    width = scene->width();
    height = scene->height() / 2;

}

Decorator::~Decorator()
{
	delete widthAnimator;
}

void Decorator::handle_leftMovement()
{
	if(x() < -width && flag)
	{
	    scene()->removeItem(this);
        flag = false;
        return;
	}
	widthAnimator->stop();
	widthAnimator->setStartValue(x());
	widthAnimator->setEndValue(x()-speed);
	widthAnimator->setDuration(500);
	widthAnimator->start();

}

void Decorator::stopMovement() {
	widthAnimator->stop();
}


