#ifndef AMIN_PLAYER_H
#define AMIN_PLAYER_H

#include "Bodyobject.h"
#include <QList>
#include <QPixmap>
#include <QTimer>
#include <QPropertyAnimation>

enum State{
    standRight,
    standLeft,
    runRight,
    runLeft
};

class Player : public Bodyobject {
    Q_OBJECT
    Q_PROPERTY(qreal Height READ y WRITE setY)
    Q_PROPERTY(qreal Width READ x WRITE setX)
private:
    State state{standRight};
    int frame{};
    QList<QPixmap *> standRightFrames{};
    QList<QPixmap *> standLeftFrames{};
    QList<QPixmap *> runRightFrames{};
    QList<QPixmap *> runLeftFrames{};
    QTimer *SRTimer{};
    QPropertyAnimation *heightAnimator{};
    QPropertyAnimation *widthAnimator{};
    int sceneHeight;
    int speed;
    bool collideGroundEnable{true};
    bool GravityEnable{true};
//    Position velocity;
public:
    ~Player() override;
    void draw(QGraphicsScene *scene) override;
    void handleRightMovement();
    void handleLeftMovement();
    void handleUpMovement();
    void handleDownMovement();
    void handleMovement(QKeyEvent *keyEvent);
    bool eventFilter(QObject *watched, QEvent *event) override;
public slots:
    void animate();
    void handleGravity();
    void stopRunAnimate();
    void collideGround();
};

#endif //AMIN_PLAYER_H
