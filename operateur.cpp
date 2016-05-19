#include "stdafx.h"

#include "Operateur.h"

const map<string, unsigned int> OperateurNumeric::listeOpNum = { {"+",2},{"-",2},{"*",2},{"/",2},{"NEG",1} };

unsigned int OperateurNumeric::getArite() const
{
	map<string, unsigned int>::const_iterator It=listeOpNum.begin();
	map<string, unsigned int>::const_iterator ItEnd = listeOpNum.end();
	while (It != ItEnd && It->first != getIdOp()) ++It;
	if (It == ItEnd) throw OperateurException("Erreur : Operateur non reconnu");
	return It->second;
}

Litterale * OperateurNumeric::appliquerOpBinaire(Litterale * l1,Litterale* l2)
{
	FabriqueLitterale& f = FabriqueLitterale::getInstance();
	Litterale* res;
	string idOp = getIdOp();
	if (idOp == "+") {
		if (LitToEnt(l1) != nullptr) {
			if (LitToEnt(l2) != nullptr) {
				res = f.fabriquer(LitToEnt(l1)->getValue() + LitToEnt(l2)->getValue());
				return res;
			}
			if (LitToRat(l2) != nullptr) {
				res = f.fabriquer((LitToRat(l2)->getDenominateur()*LitToEnt(l1)->getValue()) + LitToRat(l2)->getNumerateur(), LitToRat(l2)->getDenominateur());
				return res;
			}
			if (LitToReel(l2) != nullptr) {
				res = f.fabriquer(LitToEnt(l1)->getValue()+LitToReel(l2)->getValue());
				return res;
			}
			/*if (LitToComp(l2) != nullptr) complique */
		}
		if (LitToRat(l1) != nullptr) {

		}
		if (LitToReel(l1) != nullptr) {

		}
		if (LitToComp(l1) != nullptr) {

		}
		throw OperateurException("L'operateur" + idOp + "ne s'applique pas sur ces litterales");
	}
}

OperateurNumeric * OperateurToOpNum(Operateur * Op)
{
	return dynamic_cast<OperateurNumeric*>(Op);
}

bool isOperateur(const string & s)
{
	return (isOpNum(s));
}

bool isOpNum(const string & s)
{
	map<string, unsigned int>::const_iterator It;
	//map<string, unsigned int>::const_iterator ItEnd = OperateurNumeric::listeOpNum.end();
	for(It=OperateurNumeric::listeOpNum.begin();It!=OperateurNumeric::listeOpNum.end();++It)
		if (It->first==s) return true;
	return false;
}

FabriqueOperateur::Handler FabriqueOperateur::handler = FabriqueOperateur::Handler();

FabriqueOperateur::~FabriqueOperateur()
{
	vector<Operateur*>::iterator It;
	while (OpTab.size()) {
		It = OpTab.end();
		--It;
		supprimer(*It);
	}
}

FabriqueOperateur & FabriqueOperateur::getInstance()
{
	if (handler.instance == nullptr) handler.instance = new FabriqueOperateur;
	return *handler.instance;
}

void FabriqueOperateur::libererInstance()
{
	delete handler.instance;
	handler.instance = nullptr;
}

void FabriqueOperateur::supprimer(Operateur * Op)
{
	vector<Operateur*>::const_iterator It = OpTab.begin();
	unsigned int i = 0;
	while (It != OpTab.end() && *It != Op) {
		++It;
		i++;
	}
	if (i == OpTab.size()) throw OperateurException("Element inconnu");
	OpTab.erase(OpTab.begin() + i);
	delete(Op);
}

Operateur * FabriqueOperateur::fabriquer(const string & s)
{
	Operateur* Op;
	if (isOpNum(s)) {
		Op = new OperateurNumeric(s);
		OpTab.push_back(Op);
		return Op;
	}
	throw OperateurException("Erreur : Operateur non reconnu");
}
