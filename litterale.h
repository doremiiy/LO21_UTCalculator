#ifndef litterale_h
#define litterale_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <QVector>
#include <map>
#include <sstream>
#include <regex>
#include <QRegExp>
#include <QString>
#include <QStringRef>

#include <math.h>

class Litterale;
class LitteraleNumeric;
class Entier;
class Reel;
class Rationnel;
class Complexe;
class Atome;
class Expression;
class Programme;
class FabriqueLitterale;

using namespace std;

class LitteraleException {
private:
    QString info;
public:
    QString getInfo() const { return info; }
    LitteraleException(const QString& s):info(s){}
};


class Litterale {
public:
    virtual ~Litterale() {}
    virtual Litterale* Clone() const = 0;
    virtual QString toString() const = 0;
    //operateurs de cast
};

class LitteraleNumeric : public Litterale {
public:
    virtual LitteraleNumeric* Clone() const = 0;
    bool LitteraleNumeriquePositive(LitteraleNumeric* ln) const;
    bool LitteraleNumeriqueNegative(LitteraleNumeric* ln) const;
    bool LitteraleNumeriqueNulle(LitteraleNumeric* ln) const;
};


class Entier : public LitteraleNumeric {
private:
    int value;
public:
    Entier(int n):value(n){}
    int getValue() const { return value; }
    Entier* Clone() const;
    QString toString() const;
};

class Reel : public LitteraleNumeric {
private:
    double value;
public:
    Reel(double n):value(n){}
    double getValue() const { return value; }
    Reel* Clone() const;
    QString toString() const;
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
    QString toString() const;
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
    QString toString() const;
};

class Atome : public Litterale {
private:
    QString identificateur;
public:
    Atome(const QString& s):identificateur(s){}
    QString getIdentificateur() const { return identificateur; }
    Atome* Clone() const;
    QString toString() const;
};

class Expression : public Litterale {
private:
    QString value;
public:
    Expression(const QString& s):value(s){}
    QString getValue() const { return value; }
    QString toString() const;
    Expression* Clone() const;
    Litterale* eval() const;
};

class Programme : public Litterale {
private:
    QString value;
public:
    Programme(const QString& s):value(s){}
    QString getValue() const { return value; }
    QString toString() const;
    Programme* Clone() const;
};

class FabriqueLitterale {
private:
    QVector<Litterale*> LitTab;
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
    Litterale* fabriquerLitterale(const QString& s);
    Litterale* fabriquerLitterale(Litterale& l);

    LitteraleNumeric* fabriquerLitNum(const QString& s);
    LitteraleNumeric* fabriquerLitNum(LitteraleNumeric& l);

    Litterale* fabriquerComplexe(const QString& s);
    Litterale* fabriquerComplexe(LitteraleNumeric *l1, LitteraleNumeric *l2);
    Atome* fabriquerAtome(const QString& s);
    Atome* fabriquerAtome(Atome& a);
    Expression* fabriquerExpression(const QString & s);

    Entier* fabriquer(const Entier& e);
    Entier* fabriquer(int value);
    Reel* fabriquer(const Reel& r);
    Reel* fabriquer(double value);
    Rationnel* fabriquer(const Rationnel& ra);
    //Rationnel* fabriquer(int num, int den);
    Complexe* fabriquer(const Complexe& c);
    Atome* fabriquer(const Atome& a);

    LitteraleNumeric* fabriquer/*Rationnel*/(int n, int d);
};


int NumerateurFromStr(const QString& s);
int DenominateurFromStr(const QString& s);

bool isLitterale(const QString& s);
bool isLitteraleNumeric(const QString& s);
bool isComplexe(const QString& s);
bool isEntier(const QString& s);
bool isRationnel(const QString& s);
bool isReel(const QString& s);
bool isAtome(const QString& s);
bool isExpression(const QString& s);
bool isProgramme(const QString& s);

Entier* LitToEnt(Litterale* l);
Reel* LitToReel(Litterale* l);
Rationnel* LitToRat(Litterale* l);
Complexe* LitToComp(Litterale* l);
Atome* LitToAtome(Litterale* l);
Expression* LitToExpression(Litterale* l);
Programme* LitToProgramme(Litterale* l);

LitteraleNumeric* LitToLitNum(Litterale* l);
Entier* LitNumToEnt(LitteraleNumeric* ln);
Reel* LitNumToReel(LitteraleNumeric* ln);
Rationnel* LitNumToRat(LitteraleNumeric* ln);

const QString supprimerEspacesExpression(const QString& s);
const QString supprimerGuillemetsExpression(const QString& s);
#endif
