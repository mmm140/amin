#ifndef AMIN_PLATFORM_H
#define AMIN_PLATFORM_H

#include "Bodyobject.h"
#include <QPropertyAnimation>


class Platform : public Bodyobject {
	Q_OBJECT
	Q_PROPERTY(qreal Width READ x WRITE setX)
	QPropertyAnimation *widthAnimator{};
	int speed;
public:
    Platform(QGraphicsScene *scene);
    void draw(QGraphicsScene *scene) override;
public slots:
	handle_leftMovement();
    void stopRunAnimate();
};

Platform::~Platform();



#endif //AMIN_PLATFORM_H
