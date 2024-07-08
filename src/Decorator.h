#ifndef AMIN_DECORATOR_H
#define AMIN_DECORATOR_H

#include "Bodyobject.h"
#include <QPropertyAnimation>

class Decorator : public Bodyobject {
	Q_OBJECT
	Q_PROPERTY(qreal Width READ x WRITE setX)
	QPropertyAnimation *widthAnimator{};
	int speed;
	public:
    Decorator(QGraphicsScene *scene,int speed);
    void draw(QGraphicsScene *scene) override;
	~Decorator();
	public slots:
	void handle_leftMovement();
	void stopMovement();
};

#endif //AMIN_DECORATOR_H
