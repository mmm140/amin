#ifndef AMIN_GAME_H
#define AMIN_GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include "Platform.h"
#include "Decorator.h"
#include "Player.h"

class Game : public QObject {
    Q_OBJECT
private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    std::vector<Platform *> platforms;
    std::vector<Decorator *> decoration;
    QGraphicsTextItem *textItem;
    QTimer *closeGame{};
public:
    Player *player;
    Game();
    ~Game() override;
    int amountDistance;
    int currentDistance;
public slots:
    void handleGameOver();
    void handleVictory();
    void closeGameFunction();
	void hadleBackGroundMovement();
};

#endif //AMIN_GAME_H
