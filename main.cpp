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
	Pile *P = new Pile;
	Controleur *controleur = new Controleur(OperandeManager::getInstance(), *P);
	P->setMessage("Bienvenue");
	P->afficherPile(cout);
	system("pause");
    return 0;
}

