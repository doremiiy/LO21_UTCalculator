#include "stdafx.h"

#include "Pile.h"

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

void Pile::commande(const string & s)
{
	if (isLitterale(s)) {
		Litterale* l = f.fabriquerLitterale(s);
		push(*l);
	}
	if (isOperateur(s)) {
		Operateur* Op = o.fabriquer(s);
		appliquerOperateur(Op);
	}
}

void Pile::appliquerOperateur(Operateur * Op)
{
	if (OperateurToOpBin(Op) != nullptr) {
		if (taille() < OperateurToOpBin(Op)->getArite()) {
			o.supprimer(Op);
			throw OperateurException("Erreur : Pas assez d'arguments");
		}
		Litterale* l1=&top();
		pop();
		Litterale* l2=&top();
		pop();
		try {
			OperateurToOpBin(Op)->putLitterale(l1, l2);
			Litterale* res = Op->faireOperation();
			push(*res);
			//f.supprimer(l1);
			//f.supprimer(l2);
			return;
		}
		catch (OperateurException e) {
			push(*l2);
			push(*l1);
			o.supprimer(Op);
			e.getInfo();
		}
	}
	if (OperateurToOpUn(Op) != nullptr) {
		if (taille() < OperateurToOpUn(Op)->getArite()) {
			o.supprimer(Op);
			throw OperateurException("Erreur : Pas assez d'arguments");
		}
		Litterale* l = &top();
		pop();
		try {
			OperateurToOpUn(Op)->putLitterale(l);
			Litterale* res = Op->faireOperation();
			push(*res);
			//f.supprimer(l);
			return;
		}
		catch (OperateurException e) {
			push(*l);
			o.supprimer(Op);
			e.getInfo();
		}
	}
	if (OperateurToOpPile(Op) != nullptr) {
		if (taille() < OperateurToOpPile(Op)->getArite()) {
			o.supprimer(Op);
			throw OperateurException("Erreur : Pas assez d'arguments");
		}

	}
	throw OperateurException("Erreur : Operateur inconnu");
}

/*Memento::Memento(const vector<Item*> items)
{
	FabriqueLitterale& f = FabriqueLitterale::getInstance();
	state = *(new vector<Item*>);
	for (vector<Item*>::const_iterator It = items.begin; It != items.end(); ++It) {
		state.push_back(new Item(*f.fabriquer((*It)->getLitterale)));
	}
}*/
