#ifndef Operateur_h
#define Operateur_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <sstream>
#include <regex>

#include "Litterale.h"
#include "Pile.h"

class OperateurException;
class Operateur;
class OperateurBinaire;
class OperateurUnaire;
class OperateurPile;

using namespace std;

class OperateurException {
private:
	string info;
public:
	string getInfo() const { return info; }
	OperateurException(const string& s) :info(s) {}
};

class Operateur {
private:
	string idOp;
public:
	static const map<string, unsigned int> listeOperateurs;
	Operateur(const string& s):idOp(s){}
	virtual ~Operateur(){}
	virtual Operateur* Clone() = 0;
	virtual Litterale* faireOperation() = 0;
	const string& getIdOp() const { return  idOp; }
};

class OperateurBinaire : public Operateur {
private:
	Litterale* l1;
	Litterale* l2;
	static unsigned int arite;
public:
	OperateurBinaire(const string& s):Operateur(s),l1(nullptr),l2(nullptr){}
	static const unsigned int getArite() { return arite; }
	void putLitterale(Litterale* L1, Litterale* L2);
	Litterale* getLitterale1() const { return l1; }
	Litterale* getLitterale2() const { return l2; }
};

class OperateurUnaire : public Operateur {
private:
	Litterale* l;
	static unsigned int arite;
public:
	OperateurUnaire(const string& s):Operateur(s),l(nullptr){}
	static const unsigned int getArite() { return arite; }
	void putLitterale(Litterale* L);
	Litterale* getLitterale() const { return l; }
};

class OperateurPile : public Operateur {
private:
	static unsigned int arite;
public:
	OperateurPile(const string & s):Operateur(s){}
	static unsigned int getArite() { return arite; }
};

class OpPlus : public OperateurBinaire {
public:
	OpPlus(const string& s):OperateurBinaire(s){}
	OpPlus* Clone();
	Litterale* faireOperation();
};

class OpMoins : public OperateurBinaire {
public:
	OpMoins(const string& s) :OperateurBinaire(s) {}
	OpMoins* Clone();
	Litterale* faireOperation();
};

class OpFois : public OperateurBinaire {
public:
	OpFois(const string& s) :OperateurBinaire(s) {}
	OpFois* Clone();
	Litterale* faireOperation();
};

class OpDiviser : public OperateurBinaire {
public:
	OpDiviser(const string& s) :OperateurBinaire(s) {}
	OpDiviser* Clone();
	Litterale* faireOperation();
};

class OpNEG : public OperateurUnaire {
public:
	OpNEG(const string& s):OperateurUnaire(s){}
	OpNEG* Clone();
	Litterale* faireOperation();
};

class OpDUP : public OperateurPile {
public:
	OpDUP(const string& s):OperateurPile(s){}
	OpDUP* Clone();
	Litterale* faireOperation();
};

class OpDROP : public OperateurPile {
public:
	OpDROP(const string& s) :OperateurPile(s) {}
	OpDROP* Clone();
	Litterale* faireOperation();
};

class OpSWAP : public OperateurPile {
public:
	OpSWAP(const string& s) :OperateurPile(s) {}
	OpSWAP* Clone();
	Litterale* faireOperation();
};

class OpEGAL : public OperateurBinaire {
public:
	OpEGAL(const string& s) :OperateurBinaire(s) {}
	OpEGAL* Clone();
	Litterale* faireOperation();
};

class OpDIF : public OperateurBinaire {
public:
	OpDIF(const string& s) :OperateurBinaire(s) {}
	OpDIF* Clone();
	Litterale* faireOperation();
};

class OpSTRICTINF : public OperateurBinaire {
public:
	OpSTRICTINF(const string& s) :OperateurBinaire(s) {}
	OpSTRICTINF* Clone();
	Litterale* faireOperation();
};

class OpSTRICTSUP : public OperateurBinaire{
public:
	OpSTRICTSUP(const string& s) :OperateurBinaire(s) {}
	OpSTRICTSUP* Clone();
	Litterale* faireOperation();
};

class OpINF : public OperateurBinaire {
public:
	OpINF(const string& s) :OperateurBinaire(s) {}
	OpINF* Clone();
	Litterale* faireOperation();
};

class OpSUP : public OperateurBinaire {
public:
	OpSUP(const string& s) :OperateurBinaire(s) {}
	OpSUP* Clone();
	Litterale* faireOperation();
};

class FabriqueOperateur {
private:
	vector<Operateur*> OpTab;
	FabriqueOperateur(){}
	~FabriqueOperateur();
	void operator=(const FabriqueLitterale& f){}
	FabriqueOperateur(const FabriqueOperateur& f);
	struct Handler {
		FabriqueOperateur* instance;
		Handler() :instance(nullptr) {}
		~Handler() { delete instance; }
	};
	static Handler handler;
public:
	static FabriqueOperateur& getInstance();
	static void libererInstance();
	void supprimer(Operateur* Op);
	Operateur* fabriquer(const string& s);
};

bool isOperateur(const string& s);

OperateurBinaire* OperateurToOpBin(Operateur* Op);
OperateurUnaire* OperateurToOpUn(Operateur* Op);
OperateurPile* OperateurToOpPile(Operateur* Op);
#endif
