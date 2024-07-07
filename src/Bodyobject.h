#ifndef AMIN_BODYOBJECT_H
#define AMIN_BODYOBJECT_H

#include <QGraphicsPixmapItem>
#include "Position.h"

class Bodyobject {
protected:
    int width;
    int height;
    Position position;
    QGraphicsPixmapItem *image{nullptr};
public:
    Bodyobject(int width, int height, Position position);
    virtual void draw(QGraphicsScene *scene) = 0;
};

#endif //AMIN_BODYOBJECT_H
