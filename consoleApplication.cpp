// ConsoleApplication3.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Litterale.h"
#include "Pile.h"
#include "Operateur.h"

int main()
{
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
		}
		catch (LitteraleException e) { P->setMessage(e.getInfo()); }
		catch (OperateurException o) { P->setMessage(o.getInfo()); }
	} while (comm != "q");
	system("pause");
    return 0;
}

