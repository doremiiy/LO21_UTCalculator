//
//  main.cpp
//  Projet
//
//  Created by Rémi Di Vita on 26/04/2016.
//  Copyright © 2016 Rémi Di Vita. All rights reserved.
//

#include <iostream>
#include "computer.hpp"

using namespace std;

int main()
{
	//cout<<getNumerateur("1/2")<<"\n";
	//cout << getDenominateur("1/2") << "\n";
	string com;
	Pile *P = new Pile;
	Controleur *controleur = new Controleur(OperandeManager::getInstance(), *P);
	P->setMessage("Bienvenu");
	do {
		P->afficherPile(cout);
		cout << "Commande : ";
		cin >> com;
		controleur->commande(com);
	} while (com != "q");
	system("pause");
    return 0;
}
