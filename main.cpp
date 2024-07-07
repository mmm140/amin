#include <QApplication>
#include <QPushButton>
#include "src/Game.h"
#include "src/Player.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Game game;
    a.installEventFilter(&game.player);

    return QApplication::exec();
}
