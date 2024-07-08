#include "Game.h"
#include <QScreen>
#include <QApplication>
#include "Platform.h"

Game::Game() {
    view = new QGraphicsView();
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScreen *screen = QApplication::primaryScreen();
    view->setFixedSize(screen->geometry().width(), screen->geometry().height());
    view->showFullScreen();

    scene = new QGraphicsScene(view);
    view->setScene(scene);
    scene->setSceneRect(0, 0, view->width(), view->height());
    scene->setBackgroundBrush(QBrush("#124552"));

    player = new Player();
    player->draw(scene);
    connect(player, &Player::gameOver, this, &Game::handleGameOver);
    connect(player, &Player::gameVictory, this, &Game::handleVictory);

    auto platform = new Platform(scene);
    platform->position = Position(0,scene->height() - platform->height);
    platform->draw(scene);

    auto platform2 = new Platform(scene);
    platform2->position = Position(800,scene->height() - platform->height);
    platform2->draw(scene);
}

Game::~Game() {
    delete view;
    delete scene;
}

void Game::handleGameOver() {
    exit(0);
}

void Game::handleVictory() {

}
