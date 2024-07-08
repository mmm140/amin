#ifndef AMIN_BODYOBJECT_H
#define AMIN_BODYOBJECT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>
#include "Position.h"

class Bodyobject : public QObject, public QGraphicsPixmapItem {
protected:
    int width;
    int height;
    Position position;
public:
    Bodyobject();
    Bodyobject(int width, int height, Position position);
    virtual void draw(QGraphicsScene *scene) = 0;
};

#endif //AMIN_BODYOBJECT_H
