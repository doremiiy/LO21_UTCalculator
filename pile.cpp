#include "stdafx.h"

#include "Pile.h"

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
		o.supprimer(Op);
	}
	/*else {
		throw LitteraleException("Non Reconnu");
	}*/
}

void Pile::appliquerOperateur(Operateur * Op)
{
	if (taille() < Op->getArite()) {
		o.supprimer(Op);
		throw OperateurException("Erreur : Pas assez d'arguments");
	}
	if (OperateurToOpNum(Op) != nullptr) {
		appliquerOpNum(OperateurToOpNum(Op));
	}
	o.supprimer(Op);
	//throw OperateurException("Operateur inexistant");
}

void Pile::appliquerOpNum(OperateurNumeric * Op)
{
	if (Op->getArite() == 2) {
		Litterale* L1 = &top();
		pop();
		Litterale* L2 = &top();
		pop();
		try {
			Litterale* res = Op->appliquerOpBinaire(L1, L2);
			push(*res);
			return;
		}
		catch (OperateurException e) {
			push(*L2);
			push(*L1);
			o.supprimer(Op);
			e.getInfo();
		}
	}
}

