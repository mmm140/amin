#include "Game.h"
#include <QScreen>
#include <QApplication>
#include "Platform.h"
#include <QPainter>
#include "Decorator.h"

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

    speed = scene->width() / 10;

    player = new Player(this, speed);
    player->draw(scene);
    player->setZValue(2);
    connect(player, &Player::gameOver, this, &Game::handleGameOver);
    connect(player, &Player::gameVictory, this, &Game::handleVictory);

    auto hill = new Decorator(scene, speed);
    connect(player, &Player::BGMovement, hill, &Decorator::handle_leftMovement);
    connect(player, &Player::BGStop, hill, &Decorator::stopMovement);
    hill->position = Position(0, scene->height() * (3.0 / 8.0));
    hill->setZValue(1);
    hill->draw(scene);
    decoration.push_back(hill);

    auto platform = new Platform(scene, speed);
    connect(player, &Player::BGMovement, platform, &Platform::handle_leftMovement);
    connect(player, &Player::BGStop, platform, &Platform::stopMovement);
    platform->position = Position(-300,scene->height() - platform->height);
    platform->setZValue(3);
    platform->draw(scene);
    platforms.push_back(platform);

    auto platform2 = new Platform(scene, speed);
    connect(player, &Player::BGMovement, platform2, &Platform::handle_leftMovement);
    connect(player, &Player::BGStop, platform2, &Platform::stopMovement);
    platform2->position = Position(900,scene->height() - platform->height);
    platform2->setZValue(3);
    platform2->draw(scene);
    platforms.push_back(platform2);

    auto platform3 = new Platform(scene, speed);
    connect(player, &Player::BGMovement, platform3, &Platform::handle_leftMovement);
    connect(player, &Player::BGStop, platform3, &Platform::stopMovement);
    platform3->position = Position(1700,scene->height() - platform->height);
    platform3->setZValue(3);
    platform3->draw(scene);
    platforms.push_back(platform3);

    amountDistance = 4000;
    currentDistance = 0;
    connect(player, &Player::BGMovement, this, &Game::handleBackGroundMovement);
}

Game::~Game() {
    delete view;
    delete scene;
    qDeleteAll(platforms);
    qDeleteAll(decoration);
}

void Game::handleGameOver() {
    int width = 500;
    int height = 250;
    QRect rect((scene->width() - width) / 2, (scene->height() - height) / 2, width, height);
    scene->addRect(rect, QPen(QBrush("gray"), 3), QBrush("#21393F"));

    textItem = new QGraphicsTextItem;
    textItem->setPlainText("GameOver");
    textItem->setFont(QFont(nullptr, 50));
    textItem->setPos(rect.x() + rect.width() / 7,rect.y() + rect.height() / 7);
    textItem->setDefaultTextColor(QColor("#D62020"));
    scene->addItem(textItem);

    closeGame = new QTimer;
    closeGame->setInterval(2000);
    connect(closeGame, &QTimer::timeout, this, &Game::closeGameFunction);
    closeGame->start();
}

void Game::handleVictory() {
    int width = 500;
    int height = 250;
    QRect rect((scene->width() - width) / 2, (scene->height() - height) / 2, width, height);
    scene->addRect(rect, QPen(QBrush("gray"), 3), QBrush("#21393F"));

    textItem = new QGraphicsTextItem;
    textItem->setPlainText("Victory");
    textItem->setFont(QFont(nullptr, 50));
    textItem->setPos(rect.x() + rect.width() / 7,rect.y() + rect.height() / 7);
    textItem->setDefaultTextColor(QColor("#43D620"));
    scene->addItem(textItem);

    closeGame = new QTimer;
    closeGame->setInterval(2000);
    connect(closeGame, &QTimer::timeout, this, &Game::closeGameFunction);
    closeGame->start();
}

void Game::closeGameFunction() {
    closeGame->stop();
    scene->removeItem(textItem);
    delete textItem;
    delete closeGame;
    QApplication::exit(0);
}

void Game::handleBackGroundMovement()
{
    static int t = time(0) + 2;
    if(time(0)>=t)
    {
        srand(time(0));

        auto hill = new Decorator(scene, speed);
        connect(player, &Player::BGMovement, hill, &Decorator::handle_leftMovement);
        connect(player, &Player::BGStop, hill, &Decorator::stopMovement);
        hill->position = Position(scene->width() + (rand() % (int) scene->width()),scene->height() * (3.0 / 8.0));
        hill->setZValue(1);
        hill->draw(scene);
        decoration.push_back(hill);

        auto platform = new Platform(scene, speed);
        connect(player, &Player::BGMovement, platform, &Platform::handle_leftMovement);
        connect(player, &Player::BGStop, platform, &Platform::stopMovement);
        platform->position = Position(scene->width() + (rand() % (int) (scene->width() / 2)),scene->height() - platform->height);
        platform->setZValue(3);
        platform->draw(scene);
        platforms.push_back(platform);

        t = time(0) + 2;
    }
}

