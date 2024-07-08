#ifndef AMIN_DECORATOR_H
#define AMIN_DECORATOR_H

#include "Bodyobject.h"

class Decorator : public Bodyobject {
	public:
    Decorator(QGraphicsScene *scene);
    void draw(QGraphicsScene *scene) override;
};

#endif //AMIN_DECORATOR_H
