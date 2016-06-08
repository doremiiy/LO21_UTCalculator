#ifndef Operateur_h
#define Operateur_h

#include "Pile.h"

class OperateurException;
class Operateur;
class OperateurBinaire;
class OperateurUnaire;
class OperateurPile;

using namespace std;

/**
   \class OperateurException
   \brief Permet de lancer des message d'erreur lié au Operateur
**/
class OperateurException {
private:
    QString info;
public:
    QString getInfo() const { return info; }
    OperateurException(const QString& s) :info(s) {}
};

/**
   \class Operateur
   \brief Definit les fonctions qui s'applique au operateur

    Lorsqu’un opérateur d’arité n est appliqué alors n éléments de la pile sont dépilés. Le premier argument de l’opérateur est alors le dernier dépilé, le 2e est l’avant dernier dépilé, le 3e est l’avant-avant dernier dépilé, etc. L’application d’un opérateur peut être restreinte à certains types de littérales. Lors de la tentative d’application d’un opérateur sur un type non prévu, les arguments ne sont pas dépilés et un message d’erreur est affiché pour l’utilisateur.

**/
class Operateur {
private:
    QString idOp;
public:
    static const QMap<QString, unsigned int> listeOperateurs;
    Operateur(const QString& s):idOp(s){}
    virtual ~Operateur(){}
    virtual Operateur* Clone() = 0;
    virtual Litterale* faireOperation() = 0;
    const QString& getIdOp() const { return  idOp; }
};

/**
   \class OperateurBinaire
   \brief Operateur d'arité 2
**/
class OperateurBinaire : public Operateur {
private:
    Litterale* l1;
    Litterale* l2;
    static unsigned int arite;
public:
    OperateurBinaire(const QString& s):Operateur(s),l1(nullptr),l2(nullptr){}
    static /*const*/ unsigned int getArite() { return arite; }
    void putLitterale(Litterale* L1, Litterale* L2);
    Litterale* getLitterale1() const { return l1; }
    Litterale* getLitterale2() const { return l2; }
};

/**
   \class OperateurUnaire
   \brief Operateur d'arité 1
**/
class OperateurUnaire : public Operateur {
private:
    Litterale* l;
    static unsigned int arite;
public:
    OperateurUnaire(const QString& s):Operateur(s),l(nullptr){}
    static /*const*/ unsigned int getArite() { return arite; }
    void putLitterale(Litterale* L);
    Litterale* getLitterale() const { return l; }
};

/**
   \class OperateurPile
   \brief Operateur d'action sur la pile
**/
class OperateurPile : public Operateur {
private:
    static unsigned int arite;
public:
    OperateurPile(const QString & s):Operateur(s){}
    static unsigned int getArite() { return arite; }
};

/**
   \class OpPlus
   \brief Opérateur binaire : addition

**/
class OpPlus : public OperateurBinaire {
public:
    OpPlus(const QString& s):OperateurBinaire(s){}
    OpPlus* Clone();
    Litterale* faireOperation();
};

/**
   \class OpMoins
   \brief Opérateur binaire : soustraction
**/
class OpMoins : public OperateurBinaire {
public:
    OpMoins(const QString& s) :OperateurBinaire(s) {}
    OpMoins* Clone();
    Litterale* faireOperation();
};

/**
   \class OpFois
   \brief Opérateur binaire : multiplication
**/
class OpFois : public OperateurBinaire {
public:
    OpFois(const QString& s) :OperateurBinaire(s) {}
    OpFois* Clone();
    Litterale* faireOperation();
};

/**
   \class OpDiviser
   \brief Opérateur binaire : division.

    Une tentative de division par zéro ne modifie pas la pile et affiche un message d’erreur à l’utilisateur.

**/
class OpDiviser : public OperateurBinaire {
public:
    OpDiviser(const QString& s) :OperateurBinaire(s) {}
    OpDiviser* Clone();
    Litterale* faireOperation();
};

/**
   \class OpDIV
   \brief Opérateur binaire : division entière

    Cette opération ne peut s’appliquer que sur des littérales entières.

**/
class OpDIV : public OperateurBinaire {
public:
    OpDIV(const QString& s) :OperateurBinaire(s) {}
    OpDIV* Clone();
    Litterale* faireOperation();
};

/**
   \class OpMOD
   \brief Opérateur binaire : modulo (reste de la division entière).

   Cette opération ne peut s’appliquer que sur des littérales entières.

**/
class OpMOD : public OperateurBinaire {
public:
    OpMOD(const QString& s) :OperateurBinaire(s) {}
    OpMOD* Clone();
    Litterale* faireOperation();
};

/**
   \class OpEVAL
   \brief L’opérateur EVAL permet d’évaluer numériquement une littérale expression.

   Si la littérale expression comprend au moins un atome qui ne correspond pas au nom d’une variable, l’évaluation n’a aucune effet et un message en informe l’utilisateur. Si la littérale expression comprend au moins un atome qui correspond à l’identificateur d’un programme, l’évaluation n’a aucun effet et un message d’erreur informe l’utilisateur. Si tous les atomes de la littérales expression sont des identificateurs de variables, l’expression est évaluée numériquement.

**/
class OpEVAL : public OperateurUnaire {
public:
    OpEVAL(const QString& s) :OperateurUnaire(s) {}
    OpEVAL* Clone();
    Litterale* faireOperation();
};

/**
   \class OpNEG
   \brief Opérateur unaire : change le signe de la littérale

    (transforme un nombre négatif en nombre positif et vice et versa). Par exemple 4 NEG renvoie -4.

**/
class OpNEG : public OperateurUnaire {
public:
    OpNEG(const QString& s):OperateurUnaire(s){}
    OpNEG* Clone();
    Litterale* faireOperation();
};

/**
   \class OpDUP
   \brief Opérateur unaire : empile une nouvelle littérale identique à celle du sommet de la pile

**/
class OpDUP : public OperateurPile {
public:
    OpDUP(const QString& s):OperateurPile(s){}
    OpDUP* Clone();
    Litterale* faireOperation();
};

/**
   \class OpDROP
   \brief Opérateur unaire : dépile la littérale au sommet de la pile
**/
class OpDROP : public OperateurPile {
public:
    OpDROP(const QString& s) :OperateurPile(s) {}
    OpDROP* Clone();
    Litterale* faireOperation();
};

/**
   \class OpSWAP
   \brief Opérateur binaire : intervertit les deux derniers éléments empilés dans la pile
**/
class OpSWAP : public OperateurPile {
public:
    OpSWAP(const QString& s) :OperateurPile(s) {}
    OpSWAP* Clone();
    Litterale* faireOperation();
};

/**
   \class OpEGAL
   \brief Opérateurs binaires pour le test égal

**/
class OpEGAL : public OperateurBinaire {
public:
    OpEGAL(const QString& s) :OperateurBinaire(s) {}
    OpEGAL* Clone();
    Litterale* faireOperation();
};

/**
   \class OpDIF
   \brief Opérateurs binaires pour le test différent
**/
class OpDIF : public OperateurBinaire {
public:
    OpDIF(const QString& s) :OperateurBinaire(s) {}
    OpDIF* Clone();
    Litterale* faireOperation();
};

/**
   \class OpSTRICTINF
   \brief Opérateur binaire pour le test strictement inférieur
**/
class OpSTRICTINF : public OperateurBinaire {
public:
    OpSTRICTINF(const QString& s) :OperateurBinaire(s) {}
    OpSTRICTINF* Clone();
    Litterale* faireOperation();
};

/**
   \class OpSTRICTSUP
   \brief Opérateur binaire pour le test strictement supérieur
**/
class OpSTRICTSUP : public OperateurBinaire{
public:
    OpSTRICTSUP(const QString& s) :OperateurBinaire(s) {}
    OpSTRICTSUP* Clone();
    Litterale* faireOperation();
};

/**
   \class OpINF
   \brief Opérateur binaire pour le test inférieur ou égal
**/
class OpINF : public OperateurBinaire {
public:
    OpINF(const QString& s) :OperateurBinaire(s) {}
    OpINF* Clone();
    Litterale* faireOperation();
};

/**
   \class OpSUP
   \brief Opérateur binaire pour le test supérieur ou égal
**/
class OpSUP : public OperateurBinaire {
public:
    OpSUP(const QString& s) :OperateurBinaire(s) {}
    OpSUP* Clone();
    Litterale* faireOperation();
};

/**
   \class OpAND
   \brief Opérateur binaire : ET logique.
**/
class OpAND : public OperateurBinaire {
public:
    OpAND(const QString& s) :OperateurBinaire(s) {}
    OpAND* Clone();
    Litterale* faireOperation();
};

/**
   \class OpOR
   \brief Opérateur binaire : OU logique
**/
class OpOR : public OperateurBinaire {
public:
    OpOR(const QString& s) :OperateurBinaire(s) {}
    OpOR* Clone();
    Litterale* faireOperation();
};

/**
   \class OpNOT
   \brief Opérateur unaire : NON logique
**/
class OpNOT : public OperateurUnaire {
public:
    OpNOT(const QString& s) :OperateurUnaire(s) {}
    OpNOT* Clone();
    Litterale* faireOperation();
};

/**
   \class OpNUM
   \brief Opérateur unaire : renvoie le numérateur d’une littérale rationnelle

    Appliquée à une littérale entière, cet opérateur renvoie la littérale inchangée. Provoque une erreur sur une littérale réelle ou complexe.

**/
class OpNUM : public OperateurUnaire {
public:
    OpNUM(const QString& s) :OperateurUnaire(s) {}
    OpNUM* Clone();
    Litterale* faireOperation();
};

/**
   \class OpDEN
   \brief Opérateur unaire : renvoie le dénominateur d’une littérale rationnelle

    Renvoie la littérale entière 1 lorsqu’il est appliqué sur une littérale entière. Provoque une erreur sur une littérale réelle ou complexe.

**/
class OpDEN : public OperateurUnaire {
public:
    OpDEN(const QString& s) :OperateurUnaire(s) {}
    OpDEN* Clone();
    Litterale* faireOperation();
};

/**
   \class OpDOLLAR
   \brief Opérateur binaire : renvoie une littérale complexe

    Les deux derniers éléments de la pile qui constitueront la partie réelle et la partie imaginaire du complexe.

**/
class OpDOLLAR : public OperateurBinaire {
public:
    OpDOLLAR(const QString& s) :OperateurBinaire(s) {}
    OpDOLLAR* Clone();
    Litterale* faireOperation();
};

/**
   \class OpRE
   \brief Opérateur unaire : renvoie la partie réelle d’une littérale complexe

    La partie réelle peut être une littérale entière, rationelle ou réelle. Appliqué à une littérale entière, rationelle ou réelle, cet opérateur renvoie la littérale inchangée.

**/
class OpRE : public OperateurUnaire {
public:
    OpRE(const QString& s) :OperateurUnaire(s) {}
    OpRE* Clone();
    Litterale* faireOperation();
};

/**
   \class OpIM
   \brief Opérateur unaire : renvoie la partie iméginaire d’une littérale complexe

    La partie iméginaire  peut être une littérale entière, rationelle ou réelle. Appliqué à une littérale entière, rationelle ou réelle, cet opérateur renvoie la littérale entière 0.

**/
class OpIM : public OperateurUnaire {
public:
    OpIM(const QString& s) :OperateurUnaire(s) {}
    OpIM* Clone();
    Litterale* faireOperation();
};

/**
   \class OpUNDO
   \brief Rétablit l’état du calculateur avant la dernière opération
**/
class OpUNDO : public OperateurPile {
public:
    OpUNDO(const QString& s) :OperateurPile(s) {}
    OpUNDO* Clone();
    Litterale* faireOperation();
};

/**
   \class OpREDO
   \brief Rétablit l’état du calculateur avant l’application de la dernière opération UNDO
**/
class OpREDO : public OperateurPile {
public:
    OpREDO(const QString& s) :OperateurPile(s) {}
    OpREDO* Clone();
    Litterale* faireOperation();
};

/**
   \class OpLASTOP
   \brief Applique le dernier opérateur utilisé
**/
class OpLASTOP : public OperateurPile {
public:
    OpLASTOP(const QString& s) :OperateurPile(s) {}
    OpLASTOP* Clone();
    Litterale* faireOperation();
};

/**
   \class OpLASTARGS
   \brief Empile les littérales utilisées pour la dernière opération
**/
class OpLASTARGS : public OperateurPile {
public:
    OpLASTARGS(const QString& s) :OperateurPile(s) {}
    OpLASTARGS* Clone();
    Litterale* faireOperation();
};

/**
   \class OpCLEAR
   \brief Vide tous les éléments de la pile
**/
class OpCLEAR : public OperateurPile {
public:
    OpCLEAR(const QString& s) :OperateurPile(s) {}
    OpCLEAR* Clone();
    Litterale* faireOperation();
};

/**
   \class OpSTO
   \brief L'opérateur binaire STO permet d'associer une littérale à un identificateur

À toute littérale peut être associée un identificateur en utilisant l’opérateur binaire STO. Le premier argument est la littérale à stocker (qui peut être une littérale numérique, une littérale expression ou une littérale programme). Le deuxième est une littérale expression ne comportant qu’un atome (i.e. un atome entre guillemets). L’atome devient alors l’identificateur d’une variable s’il est associé à une littérale numérique ou l’identificateur d’un programme s’il est associé à une littérale programme.
On ne peut pas utiliser un identificateur égal à un opérateur prédéfini. Une tentative dans ce sens provoque l’affichage d’un message d’erreur. Si l’identificateur utilisé correspondait déjà à une autre variable ou un autre programme, la variable ou le programme est ecrasé par cette nouvelle valeur.
Quand un atome est utilisé sans guillemet :\n
 - s’il est l’identicateur d’une variable, il est remplacé par la valeur de la littérale associée\n
 - s’il est l’identificateur d’un programme, il provoque l’évaluation (l’exécution) du programme

**/
class OpSTO : public OperateurBinaire {
public:
    OpSTO(const QString& s) :OperateurBinaire(s) {}
    OpSTO* Clone();
    Litterale* faireOperation();
};

/**
   \class OpFORGET
   \brief L’opérateur unaire FORGET permet d’effacer la variable ou le programme associé à l’atome proposé en argument
**/
class OpFORGET : public OperateurUnaire {
public:
    OpFORGET(const QString& s) :OperateurUnaire(s) {}
    OpFORGET* Clone();
    Litterale* faireOperation();
};

/**
   \class OpIFT
   \brief Réalise un test logique

   L’opérateur binaire IFT dépile 2 arguments. Le 1er (i.e. le dernier dépilé) est un test logique. Si la valeur de ce test est vrai, le 2e argument est évalué sinon il est abandonné.

**/
class OpIFT : public OperateurBinaire {
public:
    OpIFT(const QString& s) :OperateurBinaire(s) {}
    OpIFT* Clone();
    Litterale* faireOperation();
};

/**
   \class FabriqueOperateur
   \brief Permet de crée n'importe quel objet heritant de la classe Operateur
**/
class FabriqueOperateur {
private:
    QVector<Operateur*> OpTab;
    FabriqueOperateur(){}
    ~FabriqueOperateur();
    void operator=(const FabriqueLitterale& f);
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
    Operateur* fabriquer(const QString& s);
};

//! \brief Retrourne VRAI si la chaine de caratère passé en argument est un Operateur
bool isOperateur(const QString& s);
//! \brief Retrourne VRAI si la fin de la chaine de caratère passé en argument est un Operateur
bool endIsOperateur(const QString& s);

//! \brief Convertit un pointeur sur un Operateur en pointeur vers une OperateurBinaire
OperateurBinaire* OperateurToOpBin(Operateur* Op);
//! \brief Convertit un pointeur sur un Operateur en pointeur vers une OperateurUnaire
OperateurUnaire* OperateurToOpUn(Operateur* Op);
//! \brief Convertit un pointeur sur un Operateur en pointeur vers une OperateurPile
OperateurPile* OperateurToOpPile(Operateur* Op);
#endif
