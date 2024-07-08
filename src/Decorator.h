#ifndef AMIN_DECORATOR_H
#define AMIN_DECORATOR_H

#include "Bodyobject.h"
#include <QPropertyAnimation>

class Decorator : public Bodyobject {
	Q_OBJECT
	Q_PROPERTY(qreal Width READ x WRITE setX)
	QPropertyAnimation *widthAnimator{};
	public:
    Decorator(QGraphicsScene *scene);
    void draw(QGraphicsScene *scene) override;

	public slots:
	void stopRunAnimate();
};

#endif //AMIN_DECORATOR_H
