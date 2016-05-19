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
	Operateur(const string& s):idOp(s){}
	virtual ~Operateur(){}
	const string& getIdOp() const { return  idOp; }
	virtual unsigned int getArite() const = 0;
};

class OperateurNumeric : public Operateur {
public:
	static const map<string, unsigned int> listeOpNum;
	OperateurNumeric(const string& s):Operateur(s){}
	unsigned int getArite() const;
	//Litterale* appliquerOpUnaire(Litterale* l);
	Litterale* appliquerOpBinaire(Litterale* l1,Litterale* l2);
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
bool isOpNum(const string& s);


OperateurNumeric* OperateurToOpNum(Operateur* Op);
#endif
