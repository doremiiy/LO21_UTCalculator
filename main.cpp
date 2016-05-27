// ConsoleApplication3.cpp : définit le point d'entrée pour l'application console.
//
#include <QApplication>
#include "mainWindow.h"

 int main(int argc, char* argv[]){
    //Pile& P=Pile::getInstance();
    QApplication app(argc, argv);
    MainWindow fenetre;
    fenetre.show();
    return app.exec();
}

