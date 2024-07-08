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

class Game;

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
    QTimer *runTimer{};
    QPropertyAnimation *heightAnimator{};
    QPropertyAnimation *widthAnimator{};
    int speed;
    bool collideGroundEnable{true};
    bool leftRunEnable{true};
    bool jumpEnable{true};
    bool rightRunEnable{true};
    bool collideRightEnable{true};
    bool collideLeftEnable{true};
    bool collideUpEnable{false};
    Game *game{};
    void checkGameOver();
    void collideGround();
    void collideLeftScreen();
    void collideUpScreen();
    void collideMidScreen();
    void fallInHole();
    void checkVictory();
//    Position velocity;
public:
    explicit Player(Game *game, int speed);
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
    void stopRunTimer();
signals:
    void gameOver();
    void gameVictory();
    void BGMovement();
	void BGStop();
};

#endif //AMIN_PLAYER_H
