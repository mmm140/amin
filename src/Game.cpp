#include "Game.h"

Game::Game() {
    view = new QGraphicsView();
    view->showFullScreen();

    scene = new QGraphicsScene(view);
    view->setScene(scene);
//    scene->setSceneRect(0, 0, view->width(), view->height());
    scene->setBackgroundBrush(QBrush("#124552"));
    scene->addRect(QRect(0,0,view->width(),view->height()), QPen(QBrush("red"), 5, Qt::DashLine), QBrush("yellow"));
}

Game::~Game() {
    delete view;
    delete scene;
}
