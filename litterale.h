#ifndef litterale_h
#define litterale_h

#include <QVector>
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

/**
   \class Litteral
   \brief Classe qui décrit tous les éléments manipulés par les operateurs
**/
class Litterale {
public:
    virtual ~Litterale() {}
    virtual Litterale* Clone() const = 0;
    virtual QString toString() const = 0;
    //operateurs de cast
};

/**
   \class LitteraleNumeric
   \brief Classe caractérissant les nombre appartenant à Q

   Les littérale numérique designe indifféremment une littérale entière, rationnelle ou réelle.

**/
class LitteraleNumeric : public Litterale {
public:
    virtual LitteraleNumeric* Clone() const = 0;
    bool LitteraleNumeriquePositive(LitteraleNumeric* ln) const;
    bool LitteraleNumeriqueNegative(LitteraleNumeric* ln) const;
    bool LitteraleNumeriqueNulle(LitteraleNumeric* ln) const;
};

/**
   \class Entier
   \brief Classe caractérissant les nombre appartenant à Z

   Une littérale entière est affichée sous forme décimale avec suite de chiffres pouvant commencer par le signe "-" dans le cas d’un nombre entier négatif (ex : 34 ou -52). Une littérale entière positive peut s’obtenir en saississant une suite de chiffres. Une littérale entière négative peut s’obtenir en appliquant l’opérateur NEG sur une littérale entière positive.

**/
class Entier : public LitteraleNumeric {
private:
    int value;
public:
    Entier(int n):value(n){}
    int getValue() const { return value; }
    Entier* Clone() const;
    QString toString() const;
};

/**
   \class Reel
   \brief Classe caractérissant les nombre appartenant à D (et conceptuellement a R)

   Une littérale réelle s’affiche sous forme de deux suites de chiffres séparées par le symbole "." pour séparer la partie entière de la mantisse. Lors de son affichage, la partie entière est précédée du signe - dans le cas d’un réeel négatif. La partie décimale ou la mantisse peuvent ne pas comporter de chiffres signifiant la valeur 0 (mais une des deux parties doit exister (ex : 3.14 ou .56 ou 3.). Une littérale réelle dont la matisse est nulle est simplifiée en une littérale entière. Une littérale réelle positive peut s’obtenir en saississant une suite chiffres (en utilisant "." pour séparer la partie entière de la mantisse). Une littérale réelle négative peut s’obtenir en appliquant l’opérateur NEG sur une littérale réelle positive.

**/
class Reel : public LitteraleNumeric {
private:
    double value;
public:
    Reel(double n):value(n){}
    double getValue() const { return value; }
    Reel* Clone() const;
    QString toString() const;
};

/**
   \class Rationnel
   \brief Classe caractérissant les nombre appartenant à Q

   Une littérale rationnelle s’affiche avec deux littérales entières séparées par le signe / ̧ (ex : 2/3 ou -2/3). La partie à gauche du signe / s’appelle le numérateur. La partie à droite du signe / s’appelle le dénominateur. Dès qu’une littérale rationnelle est traitée, elle est automatiquement simplifiée. Une littérale rationnelle dont le dénominateur est égal à 1 est simplifiée en une littérale entière. Une littérale rationnelle peut s’obtenir en faisant une division entre deux littérales entières.

**/
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

/**
   \class Complexe
   \brief Drecit les nombre complexe

    Une littérale complexe s’affiche avec deux littérales entières, rationnelles et/ou réelles séparées par le symbole $ (ex : -3$4.2 ou 5$-3/4). Une littérale complexe peut s’obtenir en appliquant l’opérateur binaire $ sur deux littérales entières, rationnelles et/ou réelles qui constitueront respectivement la partie réelle et la partie imaginaire de la littérale complexe.


**/
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

/**
   \class Atome
   \brief Decrit les atome

   Une littérale atome est suite de caractères composée de lettres majuscules et de chiffres et commençant par une lettre majuscule (ex: X1 ou TOTO). Une littérale atome pourra éventuellement correspondre à l’identificateur d’une variable, d’un programme ou au nom d’un opérateur prédéfini s’écrivant avec des lettres (comme DUP, SWAP, CLEAR). Une littérale atome peut s’obtenir simplement en saisissant une suite de lettres majuscules et de chiffres.

**/
class Atome : public Litterale {
private:
    QString identificateur;
public:
    Atome(const QString& s):identificateur(s){}
    QString getIdentificateur() const { return identificateur; }
    Atome* Clone() const;
    QString toString() const;
};

/**
   \class Expression
   \brief Decrit les Littérale expression

   Une littérale expression est une suite de caractères entre guillemets, i.e. entourée du caractère ’. Elle est composée de littérales entières, réelles, rationnelles, complexes ou atomes séparées par des opérateurs numériques. La notation infixe est utilisée pour les opérateurs binaires utilisant un symbole, i.e. les opérateurs +, -, * et / (ex : ’3*X+5’). La notation préfixe est utilisée avec le signe - pour former des nombres négatifs (ex : ’-2/3+Z’). La notation infixe est utisée avec le signe $ pour séparer la partie réelle de la partie imaginaire d’un nombre complexe. La notation préfixe parenthésée est utilisée dans le cas des autres opérateurs (ex : ’SIN(X)’ ou ’DIV(6,7)’). Une littérale expression peut comporter des parenthèses pour modifier les priorités entre opérateurs (ex : ’3*X1+(3+TOTO)/-2’). Une littérale expression peut s’obtenir en saisissant une suite de caractères entre guillemets. Une littérale expression ne comporte pas d’espace (des espaces peuvent éventuellement apparaître lors de la saisie par l’utilisateur mais ils sont éliminés sans changer la sémantique de la littérale expression).

**/
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

/**
   \class Programme
   \brief Decrit les Littérale programme

   Une littérale programme est une suite d’opérandes commençant par le caractère "[" et terminant par le caractère "]".

**/
class Programme : public Litterale {
private:
    QString value;
public:
    Programme(const QString& s):value(s){}
    QString getValue() const { return value; }
    QString toString() const;
    Programme* Clone() const;
    void eval() const;
};

/**
   \class FabriqueLitterale
   \brief Permet de crée n'importe quel objet heritant de la classe Litterale
**/
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
    //! \brief Frabique le singleton FabriqueLitterale si il n'exite pas et retourne un reference vers celui-ci
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
    Programme* fabriquerProgramme(const QString& s);

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

//! \brief Extrai le numerateur d'un rationelle sous forme de chaine de caractères
int NumerateurFromStr(const QString& s);
//! \brief Extrai le denominateur d'un rationelle sous forme de chaine de caractères
int DenominateurFromStr(const QString& s);

//! \brief Retrourne VRAI si la chaine de caratère passé en argument est une Litterale
bool isLitterale(const QString& s);
//! \brief Retrourne VRAI si la chaine de caratère passé en argument est une LitteraleNumeric
bool isLitteraleNumeric(const QString& s);
//! \brief Retrourne VRAI si la chaine de caratère passé en argument est un Complexe
bool isComplexe(const QString& s);
//! \brief Retrourne VRAI si la chaine de caratère passé en argument est un Entier
bool isEntier(const QString& s);
//! \brief Retrourne VRAI si la chaine de caratère passé en argument est un Rationnel
bool isRationnel(const QString& s);
//! \brief Retrourne VRAI si la chaine de caratère passé en argument est un Reel
bool isReel(const QString& s);
//! \brief Retrourne VRAI si la chaine de caratère passé en argument est un Atome
bool isAtome(const QString& s);
//! \brief Retrourne VRAI si la chaine de caratère passé en argument est une Expression
bool isExpression(const QString& s);
//! \brief Retrourne VRAI si la chaine de caratère passé en argument est Programme
bool isProgramme(const QString& s);

//! \brief Convertit un pointeur sur une Litterale en pointeur vers un Entier
Entier* LitToEnt(Litterale* l);
//! \brief Convertit un pointeur sur une Litterale en pointeur vers un Reel
Reel* LitToReel(Litterale* l);
//! \brief Convertit un pointeur sur une Litterale en pointeur vers un Rationnel
Rationnel* LitToRat(Litterale* l);
//! \brief Convertit un pointeur sur une Litterale en pointeur vers un Complexe
Complexe* LitToComp(Litterale* l);
//! \brief Convertit un pointeur sur une Litterale en pointeur vers un Atome
Atome* LitToAtome(Litterale* l);
//! \brief Convertit un pointeur sur une Litterale en pointeur vers une Expression
Expression* LitToExpression(Litterale* l);
//! \brief Convertit un pointeur sur une Litterale en pointeur vers un Programme
Programme* LitToProgramme(Litterale* l);

//! \brief Convertit un pointeur sur une Litterale en pointeur vers une LitteraleNumeric
LitteraleNumeric* LitToLitNum(Litterale* l);
//! \brief Convertit un pointeur sur une LitteraleNumeric en pointeur vers une Entier
Entier* LitNumToEnt(LitteraleNumeric* ln);
//! \brief Convertit un pointeur sur une LitteraleNumeric en pointeur vers une Reel
Reel* LitNumToReel(LitteraleNumeric* ln);
//! \brief Convertit un pointeur sur une LitteraleNumeric en pointeur vers une Rationnel
Rationnel* LitNumToRat(LitteraleNumeric* ln);

//! \brief Supprime les espaces d'une expression
const QString supprimerEspacesExpression(const QString& s);
//! \brief Supprime les guillemets d'une expression
const QString supprimerGuillemetsExpression(const QString& s);
//! \brief Supprime les parentheses d'une expression
const QString supprimerParentheseExpression(const QString& s);
//! \brief Supprime les crochets d'un expression
const QString supprimerCrochetExpression(const QString& s);

#endif
