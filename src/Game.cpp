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

    auto platform = new Platform();
    platform->draw(scene);
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
