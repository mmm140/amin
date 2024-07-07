#ifndef AMIN_GAME_H
#define AMIN_GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include "Platform.h"
#include "Decorator.h"
#include "Player.h"

class Game {
private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    std::vector<Platform> platforms;
    std::vector<Decorator> decoration;
    int amountDistance;
public:
    Player player;
    Game();
    ~Game();
    void handleGameOver();
    void handleVictory();

};

#endif //AMIN_GAME_H
