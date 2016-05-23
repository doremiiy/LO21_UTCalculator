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

class Memento;
class Item;
class Pile;

class PileException {
private:
	string info;
public:
	string getInfo() const { return info; }
	PileException(const string& s) :info(s) {}
};

class Memento {
private:
	vector<Item*> state;
public:
	Memento(const vector<Item*> items);
	vector<Item*> getState() const { return state; }
};

class CareTaker {
private:
	vector<Memento*> mementoListUndo;
	vector<Memento*> mementoListRedo;
	vector<const Litterale*> VecLitterales;
	Operateur* DernierOpApplique;
public:
	CareTaker():DernierOpApplique(nullptr){}
	vector<Item*> undo();
	vector<Item*> redo();
	Operateur* getDernierOpApplique() const { return DernierOpApplique; }
	void setDernierOpApplique(Operateur* Op);
	vector<const Litterale*> getVecLitterales() const { return VecLitterales; }
};

class Item {
private:
	Litterale& L;
public:
	Item(Litterale& l):L(*l.Clone()){}
	void setLitterale(Litterale& l) { L = *l.Clone(); }
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
	bool estVide() const { return itTab.empty(); }
	void pop();
	Litterale& top() const;
	void push(Litterale& L);	
	unsigned int taille() const { return itTab.size(); }
	void setNbToAffiche(unsigned int n) { nbAffiche = n; }
	unsigned int getNbToAffiche() const { return nbAffiche; }
	void afficherPile(ostream& f) const;
	void setMessage(const string& s) { message = s; }
	string getMessage() const { return message; }
	void commande(const string& s);
	void appliquerOperateur(Operateur* Op);
};


#endif