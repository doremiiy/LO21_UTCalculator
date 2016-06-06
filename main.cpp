/**
\mainpage Documentation de UTCalculette

\section Introduction

\file TP_Exemple.cpp
\author DI VITA Rémi, PFISTER MORGAN
\date 12/06/2016
\version 1

\brief Definition du point d'entrée pour l'application console

Ce ficher définit le point d'entrée pour l'application console.
**/

#include <QApplication>
#include "mainWindow.h"

 int main(int argc, char* argv[]){
    //Pile& P=Pile::getInstance();
    QApplication app(argc, argv);
    MainWindow fenetre;
    fenetre.show();
    return app.exec();
}

