#ifndef litterale_h
#define litterale_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <sstream>
#include <regex>

class Litterale;
class LitteraleNumeric;
class Entier;
class Reel;
class Rationnel;
class Complexe;

using namespace std;

class LitteraleException {
private:
	string info;
public:
	string getInfo() const { return info; }
	LitteraleException(const string& s):info(s){}
};


class Litterale {
public:
	virtual ~Litterale() {}
	virtual Litterale* Clone() const = 0;
	virtual string toString() const = 0;
	//operateurs de cast
};

class LitteraleNumeric : public Litterale {
public:
	virtual LitteraleNumeric* Clone() const = 0;
	//operateurs de cast
};


class Entier : public LitteraleNumeric {
private:
	int value;
public:
	Entier(int n):value(n){}
	int getValue() const { return value; }
	Entier* Clone() const;
	string toString() const;
};

class Reel : public LitteraleNumeric {
private:
	double value;
public:
	Reel(double n):value(n){}
	double getValue() const { return value; }
	Reel* Clone() const;
	string toString() const;
};

class Rationnel : public LitteraleNumeric {
private:
	int numerateur;
	int denominateur;
public:
	Rationnel(int n,int d):numerateur(n),denominateur(d){}
	int getNumerateur() const { return numerateur; }
	int getDenominateur() const { return denominateur; }
	Rationnel* Clone() const;
	string toString() const;
	void simplifier();
};

class Complexe : public Litterale {
private:
	LitteraleNumeric* pRe;
	LitteraleNumeric* pIm;
public:
	Complexe(LitteraleNumeric* r, LitteraleNumeric* i):pRe(r),pIm(i){}
	LitteraleNumeric* getPReel() const { return pRe; }
	LitteraleNumeric* getPIm() const { return pIm; }
	Complexe* Clone() const;
	string toString() const;
};

class FabriqueLitterale {
private:
	vector<Litterale*> LitTab;
	FabriqueLitterale(){}
	~FabriqueLitterale();
	FabriqueLitterale(const FabriqueLitterale& fl);
	void operator=(const FabriqueLitterale& fl);
	struct Handler {
		FabriqueLitterale* instance;
		Handler():instance(nullptr){}
		~Handler() { delete instance; }
	};
	static Handler handler;
public:
	static FabriqueLitterale& getInstance();
	static void libererInstance();
	void supprimer(Litterale* l);
	//Fabriques
	Litterale* fabriquerLitterale(const string& s);
	Litterale* fabriquerLitterale(Litterale& l);

	LitteraleNumeric* fabriquerLitNum(const string& s);
	LitteraleNumeric* fabriquerLitNum(LitteraleNumeric& l);

	Litterale* fabriquerComplexe(const string& s);
	Litterale* fabriquerComplexe(LitteraleNumeric *l1, LitteraleNumeric *l2);

	Entier* fabriquer(const Entier& e);
	Entier* fabriquer(int value);
	Reel* fabriquer(const Reel& r);
	Reel* fabriquer(double value);
	Rationnel* fabriquer(const Rationnel& ra);
	Rationnel* fabriquer(int num, int den);
	Complexe* fabriquer(const Complexe& c);

	LitteraleNumeric* fabriquerRationnel(int n, int d);
};


int NumerateurFromStr(const string& s);
int DenominateurFromStr(const string& s);

bool isLitterale(const string& s);
bool isLitteraleNumeric(const string& s);
bool isComplexe(const string& s);
bool isEntier(const string& s);
bool isRationnel(const string& s);
bool isReel(const string& s);

Entier* LitToEnt(Litterale* l);
Reel* LitToReel(Litterale* l);
Rationnel* LitToRat(Litterale* l);
Complexe* LitToComp(Litterale* l);

Entier* LitNumToEnt(LitteraleNumeric* ln);
Reel* LitNumToReel(LitteraleNumeric* ln);
Rationnel* LitNumToRat(LitteraleNumeric* ln);
#endif
