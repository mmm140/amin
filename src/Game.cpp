#include "Game.h"
#include <QScreen>
#include <QApplication>

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
    player.draw(scene);
}

Game::~Game() {
    delete view;
    delete scene;
}
