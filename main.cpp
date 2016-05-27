// ConsoleApplication3.cpp : définit le point d'entrée pour l'application console.
//
#include <QApplication>
#include "qcomputer.h"
#include "Litterale.h"
#include "Pile.h"
#include "Operateur.h"
#include "mainWindow.h"

 int main(int argc, char* argv[]){

    /*FabriqueLitterale& f = FabriqueLitterale::getInstance();
    QString at = "TOTO";
    if (isAtome(at)) {
        Litterale* a=f.fabriquerLitterale(at);
        cout << a->toQString();
    }
    system("pause");*/
    /*QString com;
    cin >> com;
    if (isOperateur(com)==true) cout<<"true";
    FabriqueOperateur& f = FabriqueOperateur::getInstance();
    Operateur* op=f.fabriquer(com);
    f.supprimer(op);
    system("pause");*/
    /*
    QString comm;
    Pile& P = Pile::getInstance();
    Controleur* C = new Controleur();
    P.setMessage("Bonjour");
    do {
        try {
            P.afficherPile(cout);
            cout << "Commande : ";
            cin >> comm;
            C->commande(comm);
            P.setMessage("Tapez une commande");
            system("cls");
        }
        catch (LitteraleException e) { P.setMessage(e.getInfo()); system("cls"); }
        catch (OperateurException o) { P.setMessage(o.getInfo()); system("cls"); }
        catch (PileException p) { P.setMessage(p.getInfo()); system("cls"); }
    } while (comm != "q");
    system("pause");
    */

    //Pile& P=Pile::getInstance();
    QApplication app(argc, argv);
    MainWindow fenetre;
    fenetre.show();
    return app.exec();
}

