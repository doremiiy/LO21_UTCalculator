#include "stdafx.h"

#include "litterale.h"

Entier * Entier::Clone() const
{
	return new Entier(*this);
}

string Entier::toString() const
{
	stringstream s;
	s << value;
	return s.str();
}

bool isEntier(const string & s)
{
	regex r("-?[[:digit:]]+");
	return regex_match(s,r);
}

Reel * Reel::Clone() const
{
	return new Reel(*this);
}

string Reel::toString() const
{
	stringstream s;
	s << value;
	return s.str();
}

bool isReel(const string & s)
{
	regex r("(-?[[:digit:]]*\\.[[:digit:]]+)|(-?[[:digit:]]+\\.[[:digit:]]*)");
	return regex_match(s, r);
}

bool isAtome(const string & s)
{
	regex r("[A-Z]([A-Z]|[0-9])*");
	return regex_match(s, r);
}

bool isExpression(const string & s)
{
	regex r("'");
	return regex_match(s, r);
}

bool isProgramme(const string & s)
{
	return false;
}

Rationnel * Rationnel::Clone() const
{
	return new Rationnel(*this);
}

string Rationnel::toString() const
{
	stringstream s;
	s << numerateur;
	s << "/";
	s << denominateur;
	return s.str();
}

bool isRationnel(const string & s)
{
	regex r("(-?[[:digit:]]+)(\\/([[:digit:]]+))");
	return regex_match(s,r);
}

void Rationnel::simplifier()
{
	if (denominateur == 0) throw LitteraleException("Erreur");
	int a = numerateur;
	int b = denominateur;
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	while (a != b) {
		if (a > b)
			a = a - b;
		else
			b = b - a;
	}
	numerateur /= a;
	denominateur /= a;
	if (denominateur < 0) {
		denominateur = -denominateur;
		numerateur = -numerateur;
	}
}

Complexe * Complexe::Clone() const
{
	return new Complexe(*this);
}

string Complexe::toString() const
{
	stringstream s;
	s << getPReel()->toString();
	s << "$";
	s << getPIm()->toString();
	return s.str();
}

string Atome::toString() const
{
	stringstream s;
	s << getIdentificateur();
	return s.str();
}

bool isComplexe(const string & s)
{
	unsigned int i, pos=s.length();
	for (i = 0; i < s.length(); i++) {
		if (s[i] == '$') pos = i;
	}
	if (pos == s.length()) return false;
	return (isLitteraleNumeric(s.substr(0, pos)) && isLitteraleNumeric(s.substr(pos + 1)));
}

bool isLitteraleNumeric(const string& s)
{
	return (isEntier(s) || isReel(s) || isRationnel(s));
}

LitteraleNumeric * LitToLitNum(Litterale * l)
{
	return dynamic_cast<LitteraleNumeric*>(l);
}

Entier * LitNumToEnt(LitteraleNumeric * ln)
{
	return dynamic_cast<Entier*>(ln);
}

Reel * LitNumToReel(LitteraleNumeric * ln)
{
	return dynamic_cast<Reel*>(ln);
}

Rationnel * LitNumToRat(LitteraleNumeric * ln)
{
	return dynamic_cast<Rationnel*>(ln);
}

bool isLitterale(const string& s)
{
	return (isLitteraleNumeric(s) || isComplexe(s) || isExpression(s) || isAtome(s));
}

Entier * LitToEnt(Litterale * l)
{
	return dynamic_cast<Entier*>(l);
}

Reel * LitToReel(Litterale * l)
{
	return dynamic_cast<Reel*>(l);
}

Rationnel * LitToRat(Litterale * l)
{
	return dynamic_cast<Rationnel*>(l);
}

Complexe * LitToComp(Litterale * l)
{
	return dynamic_cast<Complexe*>(l);
}

Atome * LitToAtome(Litterale * l)
{
	return dynamic_cast<Atome*>(l);
}

Expression * LitToExpression(Litterale * l)
{
	return dynamic_cast<Expression*>(l);
}

Programme * LitToProgramme(Litterale * l)
{
	return dynamic_cast<Programme*>(l);
}

FabriqueLitterale::Handler FabriqueLitterale::handler = FabriqueLitterale::Handler();

FabriqueLitterale::~FabriqueLitterale()
{
	vector<Litterale*>::iterator It;
	while (LitTab.size()) {
		It = LitTab.end();
		--It;
		supprimer(*It);
	}
}

FabriqueLitterale & FabriqueLitterale::getInstance()
{
	if (handler.instance == nullptr) handler.instance = new FabriqueLitterale;
	return *handler.instance;
}

void FabriqueLitterale::libererInstance()
{
	delete handler.instance;
	handler.instance = nullptr;
}

void FabriqueLitterale::supprimer(Litterale * l)
{
	vector<Litterale*>::const_iterator It = LitTab.begin();
	unsigned int i = 0;
	while (It != LitTab.end() && *It != l) {
		++It;
		i++;
	}
	if (i == LitTab.size()) throw LitteraleException("Element inconnu");
	/*if (LitToComp(l) != nullptr) {
		supprimer(LitToComp(l)->getPReel());
		supprimer(LitToComp(l)->getPIm());
	}*/
	LitTab.erase(LitTab.begin() + i);
	//delete l;
}

Litterale * FabriqueLitterale::fabriquerLitterale(const string & s)
{
	Litterale *L;
	if (isLitteraleNumeric(s)) {
		L = fabriquerLitNum(s);
		return L;
	}
	if (isComplexe(s)) {
		L = fabriquerComplexe(s);
		return L;
	}
	if (isAtome(s)) {
		L=fabriquerAtome(s);
		return L;
	}
	throw LitteraleException("Erreur : pas de litterale correspondant");
}

Atome * FabriqueLitterale::fabriquerAtome(const string & s)
{
	Atome* a = new Atome(s);
	LitTab.push_back(a);
	return a;
}


Litterale * FabriqueLitterale::fabriquerLitterale(Litterale & l)
{
	Litterale* tL = l.Clone();
	LitTab.push_back(tL);
	return &l;
}

LitteraleNumeric * FabriqueLitterale::fabriquerLitNum(const string & s)
{
	if (isEntier(s)) {
		Entier* e = new Entier(atoi(s.c_str()));
		LitTab.push_back(e);
		return e;
	}

	if (isReel(s)) {
		int i = 0;
		while (s[i] != '.') i++;
		if (atoi(s.substr(i + 1).c_str()) == 0) {
			Entier* e = new Entier(atoi(s.c_str()));
			LitTab.push_back(e);
			return e;
		}
		else {
			int m = atoi(s.c_str());
			int e = atoi(s.substr(i + 1).c_str());
			stringstream s;
			s << e;
			Reel* r = new Reel(m+(e/pow(10,s.str().length())));
			LitTab.push_back(r);
			return r;
		}
	}

	if (isRationnel(s)) {
		return fabriquer/*Rationnel*/(NumerateurFromStr(s), DenominateurFromStr(s));
	}
}

Litterale * FabriqueLitterale::fabriquerComplexe(const string & s)
{
	unsigned int i, pos = s.length();
	for(i=0;i<s.length();i++){
		if (s[i] == '$') pos = i;
	}
	if (pos == s.length()) throw LitteraleException("Erreur");
	if (pos != s.length()) {
		LitteraleNumeric* pRe = fabriquerLitNum(s.substr(0, pos));
		LitteraleNumeric* pIm = fabriquerLitNum(s.substr(pos + 1));
		//Test si partie imaginaire nulle
		Entier *im = dynamic_cast<Entier*>(pIm);
		if (im != nullptr && im->getValue() == 0) {
			supprimer(pIm);
			LitTab.push_back(pRe);
			return pRe;
		}
		else {
			Complexe* c = new Complexe(pRe, pIm);
			LitTab.push_back(c);
			return c;
		}
	}

}

Entier * FabriqueLitterale::fabriquer(const Entier & e)
{
	Entier* eTmp = e.Clone();
	LitTab.push_back(eTmp);
	return eTmp;
}

Reel * FabriqueLitterale::fabriquer(const Reel & r)
{
	Reel* rTmp = r.Clone();
	LitTab.push_back(rTmp);
	return rTmp;
}

Rationnel * FabriqueLitterale::fabriquer(const Rationnel & ra)
{
	Rationnel* raTmp = ra.Clone();
	LitTab.push_back(raTmp);
	return raTmp;
}

Complexe * FabriqueLitterale::fabriquer(const Complexe & c)
{
	Complexe* cTmp = c.Clone();
	LitTab.push_back(cTmp);
	return cTmp;
}

Atome * FabriqueLitterale::fabriquer(const Atome & a)
{
	Atome* aTmp = a.Clone();
	LitTab.push_back(aTmp);
	return aTmp;
}

Entier * FabriqueLitterale::fabriquer(int value)
{
	Entier* e = new Entier(value);
	LitTab.push_back(e);
	return e;
}

Reel * FabriqueLitterale::fabriquer(double value)
{
	Reel* r = new Reel(value);
	LitTab.push_back(r);
	return r;
}

/*Rationnel * FabriqueLitterale::fabriquer(int num, int den)
{
	Rationnel* ra = new Rationnel(num,den);
	ra->simplifier();
	LitTab.push_back(ra);
	return ra;
}*/

Litterale * FabriqueLitterale::fabriquerComplexe(LitteraleNumeric * l1, LitteraleNumeric * l2)
{
	FabriqueLitterale& f = FabriqueLitterale::getInstance();
	Complexe * c=new Complexe(l1,l2);
	if (LitNumToEnt(c->getPIm()) != nullptr && LitNumToEnt(c->getPIm())->getValue() == 0) {
		LitteraleNumeric* ln = f.fabriquerLitNum(*c->getPReel());
		delete c;
		LitTab.push_back(ln);
		return ln;
	}
	else {
		LitTab.push_back(c);
		return c;
	}
}

LitteraleNumeric * FabriqueLitterale::fabriquerLitNum(LitteraleNumeric & l)
{
	LitteraleNumeric* tLn = l.Clone();
	LitTab.push_back(tLn);
	return tLn;
}

Atome * FabriqueLitterale::fabriquerAtome(Atome & a)
{
	Atome* tA = a.Clone();
	LitTab.push_back(tA);
	return tA;
}

LitteraleNumeric * FabriqueLitterale::fabriquer/*Rationnel*/(int n, int d)
{
	if (d == 0) throw LitteraleException("Erreur : denominateur nul");
	Rationnel* r = new Rationnel(n, d);
	r->simplifier();
	if (r->getDenominateur() == 1) {
		Entier* e = new Entier(r->getNumerateur());
		LitTab.push_back(e);
		delete r;
		return e;
	}
	if (r->getNumerateur() == 0) {
		Entier* e = new Entier(r->getNumerateur());
		LitTab.push_back(e);
		delete r;
		return e;
	}
	else {
		LitTab.push_back(r);
		return r;
	}
}

Atome * Atome::Clone() const
{
	return new Atome(*this);
}

int NumerateurFromStr(const string & s)
{
	if (isRationnel(s)) {
		unsigned int i = 0;
		while (s[i] != '/') i++;
		return atoi(s.substr(0, i).c_str());
	}
}

int DenominateurFromStr(const string & s)
{
	if (isRationnel(s)) {
		unsigned int i = 0;
		while (s[i] != '/') i++;
		return atoi(s.substr(i + 1).c_str());
	}
}

string Expression::toString() const
{
	return value;
}

Expression * Expression::Clone() const
{
	return new Expression(*this);
}

string Programme::toString() const
{
	return value;
}

Programme * Programme::Clone() const
{
	return new Programme(*this);
}

bool LitteraleNumeric::LitteraleNumeriquePositive(LitteraleNumeric* ln) const
{
	if (LitNumToEnt(ln) != nullptr) {
		if (LitNumToEnt(ln)->getValue() > 0) 
			return true;
		return false;
	}
	if (LitNumToRat(ln) != nullptr) {
		if ((LitNumToRat(ln)->getNumerateur() > 0) && (LitNumToRat(ln)->getDenominateur() > 0) || (LitNumToRat(ln)->getNumerateur() < 0) && (LitNumToRat(ln)->getDenominateur() < 0))
			return true;
		return false;
	}
	if (LitNumToReel(ln) != nullptr) {
		if (LitNumToReel(ln)->getValue() > 0)
			return true;
		return false;
	}
	throw LitteraleException("Erreur");
}

bool LitteraleNumeric::LitteraleNumeriqueNegative(LitteraleNumeric * ln) const
{
	if (LitNumToEnt(ln) != nullptr) {
		if (LitNumToEnt(ln)->getValue() < 0)
			return true;
		return false;
	}
	if (LitNumToRat(ln) != nullptr) {
		if ((LitNumToRat(ln)->getNumerateur() > 0) && (LitNumToRat(ln)->getDenominateur() < 0) || (LitNumToRat(ln)->getNumerateur() < 0) && (LitNumToRat(ln)->getDenominateur() > 0))
			return true;
		return false;
	}
	if (LitNumToReel(ln) != nullptr) {
		if (LitNumToReel(ln)->getValue() < 0)
			return true;
		return false;
	}
	throw LitteraleException("Erreur");
}
