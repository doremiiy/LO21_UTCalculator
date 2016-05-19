#ifndef Pile_h
#define Pile_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <sstream>
#include <regex>

#include "Litterale.h"
#include "Operateur.h"

using namespace std;

class Item {
private:
	Litterale& L;
public:
	Item(Litterale& l):L(l){}
	void setLitterale(Litterale& l) { L = l; }
	Litterale& getLitterale() const { return L; }
};

class Pile {
private:
	vector<Item*> itTab;
	unsigned int nbAffiche;
	FabriqueLitterale& f;
	FabriqueOperateur& o;
	string message;
public:
	Pile() :nbAffiche(5), f(FabriqueLitterale::getInstance()), o(FabriqueOperateur::getInstance()), message("") {
		vector<Item*> itTab = *(new vector<Item*>);
	}
	~Pile() { FabriqueLitterale::libererInstance(); }
	bool estVide() { return itTab.empty(); }
	void pop() { itTab.pop_back(); }
	Litterale& top() const { return itTab.back()->getLitterale(); }
	void push(Litterale& L) { Item* i = new Item(L); itTab.push_back(i); }
	unsigned int taille() const { return itTab.size(); }
	void setNbToAffiche(unsigned int n) { nbAffiche = n; }
	unsigned int getNbToAffiche() const { return nbAffiche; }
	void afficherPile(ostream& f) const;
	void setMessage(const string& s) { message = s; }
	string getMessage() const { return message; }
	void commande(const string& s);
	void appliquerOperateur(Operateur* Op);
	void appliquerOpNum(OperateurNumeric* Op);
};


#endif