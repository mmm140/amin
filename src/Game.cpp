#include "Game.h"
#include <QScreen>
#include <QApplication>
#include "Platform.h"
#include <QPainter>

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
    platform->position = Position(-300,scene->height() - platform->height);
    platform->draw(scene);

    auto platform2 = new Platform(scene);
    platform2->position = Position(900,scene->height() - platform->height);
    platform2->draw(scene);
}

Game::~Game() {
    delete view;
    delete scene;
}

void Game::handleGameOver() {
    int width = 500;
    int height = 250;
    QRect rect((scene->width() - width) / 2, (scene->height() - height) / 2, width, height);
    scene->addRect(rect, QPen(QBrush("gray"), 3), QBrush("#21393F"));

    gameOverText = new QGraphicsTextItem;
    gameOverText->setPlainText("GameOver");
    gameOverText->setFont(QFont(nullptr, 50));
    gameOverText->setPos(rect.x() + rect.width() / 7,rect.y() + rect.height() / 7);
    gameOverText->setDefaultTextColor(QColor("#D62020"));
    scene->addItem(gameOverText);

    closeGame = new QTimer;
    closeGame->setInterval(2000);
    connect(closeGame, &QTimer::timeout, this, &Game::closeGameFunction);
    closeGame->start();
}

void Game::handleVictory() {

}

void Game::closeGameFunction() {
    closeGame->stop();
    scene->removeItem(gameOverText);
    delete gameOverText;
    delete closeGame;
    QApplication::exit(0);
}
