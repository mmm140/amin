#ifndef AMIN_PLATFORM_H
#define AMIN_PLATFORM_H

#include "Bodyobject.h"

class Platform : public Bodyobject {
public:
    void draw(QGraphicsScene *scene) override;
};

#endif //AMIN_PLATFORM_H
