#ifndef AMIN_PLATFORM_H
#define AMIN_PLATFORM_H

#include "Bodyobject.h"
#include <QPropertyAnimation>


class Platform : public Bodyobject {
	Q_OBJECT
	Q_PROPERTY(qreal Width READ x WRITE setX)
	QPropertyAnimation *widthAnimator{};
	int speed;
	int lastx;
public:
    Platform(QGraphicsScene *scene, int speed);
    ~Platform();
    void draw(QGraphicsScene *scene) override;
public slots:
	void handle_leftMovement();
    void stopMovement();
};

#endif //AMIN_PLATFORM_H
