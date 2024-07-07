#ifndef AMIN_PLAYER_H
#define AMIN_PLAYER_H

#include "Bodyobject.h"
#include <QList>
#include <QPixmap>
#include <QTimer>
#include <QPropertyAnimation>

class Player : public Bodyobject {
    Q_OBJECT
    Q_PROPERTY(qreal Height READ (image->y) WRITE (image->setY))
private:
    int frame{};
    QList<QPixmap *> standRightFrames{};
    QList<QPixmap *> standLeftFrames{};
    QList<QPixmap *> runRightFrames{};
    QList<QPixmap *> runLeftFrames{};
    QTimer *standTimer{};
    QTimer *runTimer{};
    QPropertyAnimation *heightAnimator{};
    int sceneHeight;
    int speed;
    Position velocity;
public:
    Player();
    ~Player();
    void draw(QGraphicsScene *scene) override;
    void handleRightMovement();
    void handleLeftMovement();
    void handleUpMovement();
    void handleDownMovement();
    void handleMovement(QKeyEvent *keyEvent);
    bool eventFilter(QObject *watched, QEvent *event);
public slots:
    void standRightAnimate();
    void handleGravity();
};

#endif //AMIN_PLAYER_H
