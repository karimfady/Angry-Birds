#include "birdieblast.h"

#include <QApplication>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    BirdieBlast w(0);
    w.show();

    return a.exec();
}
