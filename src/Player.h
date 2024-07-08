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
    Q_PROPERTY(qreal Height READ (image->y) WRITE (image->setY))
    Q_PROPERTY(qreal Width READ (image->x) WRITE (image->setX))
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
    Position velocity;
public:
    Player();
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
};

#endif //AMIN_PLAYER_H
