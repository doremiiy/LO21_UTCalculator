// ConsoleApplication3.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Litterale.h"
#include "Pile.h"
#include "Operateur.h"

int main()
{
	/*FabriqueLitterale& f = FabriqueLitterale::getInstance();
	string at = "TOTO";
	if (isAtome(at)) {
		Litterale* a=f.fabriquerLitterale(at);
		cout << a->toString();
	}
	system("pause");*/
	/*string com;
	cin >> com;
	if (isOperateur(com)==true) cout<<"true";
	FabriqueOperateur& f = FabriqueOperateur::getInstance();
	Operateur* op=f.fabriquer(com);
	f.supprimer(op);
	system("pause");*/
	string comm;
	Pile *P = new Pile;
	P->setMessage("Bonjour");
	do {
		try {
			P->afficherPile(cout);
			cout << "Commande : ";
			cin >> comm;
			P->commande(comm);
			P->setMessage("Tapez une commande");
			system("cls");
		}
		catch (LitteraleException e) { P->setMessage(e.getInfo()); system("cls"); }
		catch (OperateurException o) { P->setMessage(o.getInfo()); system("cls"); }
	} while (comm != "q");
	system("pause");
    return 0;
}

