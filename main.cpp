#include <QApplication>
#include <QPushButton>
#include "src/Game.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Game game;

    return QApplication::exec();
}
