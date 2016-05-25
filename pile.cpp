#include "stdafx.h"

#include "Pile.h"

Pile::Handler Pile::handler = Pile::Handler();

Pile::~Pile()
{
	FabriqueLitterale::libererInstance(); 
	FabriqueOperateur::libererInstance();
}

Pile& Pile::getInstance()
{
	if (handler.instance == nullptr) handler.instance = new Pile;
	return *handler.instance;
}

void Pile::libererInstance()
{
	delete handler.instance;
	handler.instance = nullptr;
}

void Pile::pop()
{
	if (!estVide())
		itTab.pop_back();
	else
		throw PileException("Erreur : pile vide");
}

Litterale & Pile::top() const
{
	if (!estVide()) 
		return itTab.back()->getLitterale();
	throw PileException("Erreur : pile vide");
}

void Pile::push(Litterale & L)
{
	itTab.push_back(new Item(L));
}

void Pile::afficherPile(ostream & f) const
{
	f << "****************************\n";
	f << "M : " << message << "\n";
	f << "------------------------------\n";
	vector<Item*>::const_iterator It = itTab.begin();
	for (unsigned int i = nbAffiche; i > 0; i--) {
		if (i <= taille()) {
			f << i << ": " << (*It)->getLitterale().toString() << "\n";
			++It;
		}
		else f << i << ": ";
		cout << "\n";
	}
	f << "---------------------------------\n";
}

/*void Pile::setState(vector<Item*> items)
{
	FabriqueLitterale& f = FabriqueLitterale::getInstance();
	vector<Item*> state = *(new vector<Item*>);
	for (vector<Item*>::const_iterator It = items.begin(); It != items.end(); ++It) {
		state.push_back(new Item(*f.fabriquerLitterale((*It)->getLitterale())));
	}
	itTab.clear();
	itTab = state;
	state.clear();
}*/

/*Memento::Memento(const vector<Item*> items)
{
	FabriqueLitterale& f = FabriqueLitterale::getInstance();
	state = *(new vector<Item*>);
	for (vector<Item*>::const_iterator It = items.begin(); It != items.end(); ++It) {
		state.push_back(new Item(*f.fabriquerLitterale((*It)->getLitterale())));
	}
}*/

/*vector<Item*> CareTaker::undo()
{
		
}

vector<Item*> CareTaker::redo()
{
	
}*/

void Controleur::commande(const string & s)
{
	FabriqueLitterale& f = FabriqueLitterale::getInstance();
	FabriqueOperateur& o = FabriqueOperateur::getInstance();
	if (isOperateur(s)) {
		Operateur* Op = o.fabriquer(s);
		appliquerOperateur(Op);
	}
	else {
		if (isLitterale(s)) {
			Litterale* l = f.fabriquerLitterale(s);
			p.push(*l);
		}
	}
}

void Controleur::appliquerOperateur(Operateur * Op)
{
	FabriqueLitterale& f = FabriqueLitterale::getInstance();
	FabriqueOperateur& o = FabriqueOperateur::getInstance();
	if (OperateurToOpBin(Op) != nullptr) {
		if (p.taille() < OperateurToOpBin(Op)->getArite()) {
			o.supprimer(Op);
			throw OperateurException("Erreur : Pas assez d'arguments");
		}
		Litterale* l1 = &p.top();
		p.pop();
		Litterale* l2 = &p.top();
		p.pop();
		try {
			OperateurToOpBin(Op)->putLitterale(l1, l2);
			Litterale* res = Op->faireOperation();
			if (res != nullptr)
				p.push(*res);
			else throw PileException("Erreur ");
			return;
		}
		catch (OperateurException e) {
			p.push(*l2);
			p.push(*l1);
			o.supprimer(Op);
			e.getInfo();
		}
	}
	if (OperateurToOpUn(Op) != nullptr) {
		if (p.taille() < OperateurToOpUn(Op)->getArite()) {
			o.supprimer(Op);
			throw OperateurException("Erreur : Pas assez d'arguments");
		}
		Litterale* l = &p.top();
		p.pop();
		try {
			OperateurToOpUn(Op)->putLitterale(l);
			Litterale* res = Op->faireOperation();
			p.push(*res);
			return;
		}
		catch (OperateurException e) {
			p.push(*l);
			o.supprimer(Op);
			e.getInfo();
		}
	}
	if (OperateurToOpPile(Op) != nullptr) {
		try {
			Litterale* res = OperateurToOpPile(Op)->faireOperation();
			if (res != nullptr) p.push(*res);
			return;
		}
		catch (OperateurException e) {
			o.supprimer(Op);
			e.getInfo();
		}
	}
	throw OperateurException("Erreur : Operateur inconnu");
}
