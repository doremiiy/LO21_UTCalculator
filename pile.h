#ifndef Pile_h
#define Pile_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <list>

#include "Litterale.h"
#include "Operateur.h"

using namespace std;

class Operateur;
class PileException;
class Item;
class Pile;

class PileException {
private:
	string info;
public:
	string getInfo() const { return info; }
	PileException(const string& s) :info(s) {}
};

class Item {
private:
	Litterale& L;
public:
	Item(Litterale& l) :L(*l.Clone()) {}
	void setLitterale(Litterale& l) { L = *l.Clone(); }
	Litterale& getLitterale() const { return L; }
};

/*class Memento {
private:
	vector<Item*> state;
public:
	Memento(const vector<Item*> items);
	vector<Item*> getState() const { return state; }
};*/

class Pile {
private:
	vector<Item*> itTab;
	unsigned int nbAffiche;
	string message;
	Pile() :nbAffiche(5), message("") {
		vector<Item*> itTab = *(new vector<Item*>);
	}
	~Pile();
	void operator=(const Pile& p) {}
	Pile(const Pile& p);
	struct Handler {
		Pile* instance;
		Handler() :instance(nullptr) {}
		~Handler() { delete instance; }
	};
	static Handler handler;
public:
	static Pile& getInstance();
	static void libererInstance();
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
	//void setState(vector<Item*> items);
	//vector<Item*> getState() { return itTab; }
	//Memento saveStateToMemento() { return new Memento(itTab); }
	//void getStateFromMemento() { itTab = Memento.getState(); }
};

/*class CareTaker {
private:
	list<Memento> mementoList;
	//Operateur* DernierOpApplique;
public:
	//CareTaker():DernierOpApplique(nullptr){}
	//Operateur* getDernierOpApplique() const { return DernierOpApplique; }
	//void setDernierOpApplique(Operateur* Op) { delete DernierOpApplique; DernierOpApplique = Op->Clone(); }
	//vector<const Litterale*> getListLitterales() const { return ListLitterales; }
	//void clearListLitterales() { ListLitterales.clear(); }
	void Add(Memento state) { mementoList.push_back(state); }
	Memento get() {return mementoList.}
	vector<Item*> undo();
	vector<Item*> redo();
};*/

class Controleur {
private:
	Pile& p;
	//CareTaker& ct;
public:
	Controleur() :p(Pile::getInstance()) {}
	//void saveOp(Operateur* Op);
	void commande(const string& s);
	void appliquerOperateur(Operateur* Op);
};


#endif