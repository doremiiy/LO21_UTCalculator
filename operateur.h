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
   \brief
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
   \brief
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
   \brief
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
   \brief
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
   \brief
**/
class OpPlus : public OperateurBinaire {
public:
    OpPlus(const QString& s):OperateurBinaire(s){}
    OpPlus* Clone();
    Litterale* faireOperation();
};

/**
   \class OpMoins
   \brief
**/
class OpMoins : public OperateurBinaire {
public:
    OpMoins(const QString& s) :OperateurBinaire(s) {}
    OpMoins* Clone();
    Litterale* faireOperation();
};

/**
   \class OpFois
   \brief
**/
class OpFois : public OperateurBinaire {
public:
    OpFois(const QString& s) :OperateurBinaire(s) {}
    OpFois* Clone();
    Litterale* faireOperation();
};

/**
   \class OpDiviser
   \brief
**/
class OpDiviser : public OperateurBinaire {
public:
    OpDiviser(const QString& s) :OperateurBinaire(s) {}
    OpDiviser* Clone();
    Litterale* faireOperation();
};

/**
   \class OpDIV
   \brief
**/
class OpDIV : public OperateurBinaire {
public:
    OpDIV(const QString& s) :OperateurBinaire(s) {}
    OpDIV* Clone();
    Litterale* faireOperation();
};

/**
   \class OpMOD
   \brief
**/
class OpMOD : public OperateurBinaire {
public:
    OpMOD(const QString& s) :OperateurBinaire(s) {}
    OpMOD* Clone();
    Litterale* faireOperation();
};

/**
   \class OpEVAL
   \brief
**/
class OpEVAL : public OperateurUnaire {
public:
    OpEVAL(const QString& s) :OperateurUnaire(s) {}
    OpEVAL* Clone();
    Litterale* faireOperation();
};

/**
   \class OpNEG
   \brief
**/
class OpNEG : public OperateurUnaire {
public:
    OpNEG(const QString& s):OperateurUnaire(s){}
    OpNEG* Clone();
    Litterale* faireOperation();
};

/**
   \class OpDUP
   \brief
**/
class OpDUP : public OperateurPile {
public:
    OpDUP(const QString& s):OperateurPile(s){}
    OpDUP* Clone();
    Litterale* faireOperation();
};

/**
   \class OpDROP
   \brief
**/
class OpDROP : public OperateurPile {
public:
    OpDROP(const QString& s) :OperateurPile(s) {}
    OpDROP* Clone();
    Litterale* faireOperation();
};

/**
   \class OpSWAP
   \brief
**/
class OpSWAP : public OperateurPile {
public:
    OpSWAP(const QString& s) :OperateurPile(s) {}
    OpSWAP* Clone();
    Litterale* faireOperation();
};

/**
   \class OpEGAL
   \brief
**/
class OpEGAL : public OperateurBinaire {
public:
    OpEGAL(const QString& s) :OperateurBinaire(s) {}
    OpEGAL* Clone();
    Litterale* faireOperation();
};

/**
   \class OpDIF
   \brief
**/
class OpDIF : public OperateurBinaire {
public:
    OpDIF(const QString& s) :OperateurBinaire(s) {}
    OpDIF* Clone();
    Litterale* faireOperation();
};

/**
   \class OpSTRICTINF
   \brief
**/
class OpSTRICTINF : public OperateurBinaire {
public:
    OpSTRICTINF(const QString& s) :OperateurBinaire(s) {}
    OpSTRICTINF* Clone();
    Litterale* faireOperation();
};

/**
   \class OpSTRICTSUP
   \brief
**/
class OpSTRICTSUP : public OperateurBinaire{
public:
    OpSTRICTSUP(const QString& s) :OperateurBinaire(s) {}
    OpSTRICTSUP* Clone();
    Litterale* faireOperation();
};

/**
   \class OpINF
   \brief
**/
class OpINF : public OperateurBinaire {
public:
    OpINF(const QString& s) :OperateurBinaire(s) {}
    OpINF* Clone();
    Litterale* faireOperation();
};

/**
   \class OpSUP
   \brief
**/
class OpSUP : public OperateurBinaire {
public:
    OpSUP(const QString& s) :OperateurBinaire(s) {}
    OpSUP* Clone();
    Litterale* faireOperation();
};

/**
   \class OpAND
   \brief
**/
class OpAND : public OperateurBinaire {
public:
    OpAND(const QString& s) :OperateurBinaire(s) {}
    OpAND* Clone();
    Litterale* faireOperation();
};

/**
   \class OpOR
   \brief
**/
class OpOR : public OperateurBinaire {
public:
    OpOR(const QString& s) :OperateurBinaire(s) {}
    OpOR* Clone();
    Litterale* faireOperation();
};

/**
   \class OpNOT
   \brief
**/
class OpNOT : public OperateurUnaire {
public:
    OpNOT(const QString& s) :OperateurUnaire(s) {}
    OpNOT* Clone();
    Litterale* faireOperation();
};

/**
   \class OpNUM
   \brief
**/
class OpNUM : public OperateurUnaire {
public:
    OpNUM(const QString& s) :OperateurUnaire(s) {}
    OpNUM* Clone();
    Litterale* faireOperation();
};

/**
   \class OpDEN
   \brief
**/
class OpDEN : public OperateurUnaire {
public:
    OpDEN(const QString& s) :OperateurUnaire(s) {}
    OpDEN* Clone();
    Litterale* faireOperation();
};

/**
   \class OpDOLLAR
   \brief
**/
class OpDOLLAR : public OperateurBinaire {
public:
    OpDOLLAR(const QString& s) :OperateurBinaire(s) {}
    OpDOLLAR* Clone();
    Litterale* faireOperation();
};

/**
   \class OpRE
   \brief
**/
class OpRE : public OperateurUnaire {
public:
    OpRE(const QString& s) :OperateurUnaire(s) {}
    OpRE* Clone();
    Litterale* faireOperation();
};

/**
   \class OpIM
   \brief
**/
class OpIM : public OperateurUnaire {
public:
    OpIM(const QString& s) :OperateurUnaire(s) {}
    OpIM* Clone();
    Litterale* faireOperation();
};

/**
   \class OpUNDO
   \brief
**/
class OpUNDO : public OperateurPile {
public:
    OpUNDO(const QString& s) :OperateurPile(s) {}
    OpUNDO* Clone();
    Litterale* faireOperation();
};

/**
   \class OpREDO
   \brief
**/
class OpREDO : public OperateurPile {
public:
    OpREDO(const QString& s) :OperateurPile(s) {}
    OpREDO* Clone();
    Litterale* faireOperation();
};

/**
   \class OpLASTOP
   \brief
**/
class OpLASTOP : public OperateurPile {
public:
    OpLASTOP(const QString& s) :OperateurPile(s) {}
    OpLASTOP* Clone();
    Litterale* faireOperation();
};

/**
   \class OpLASTARG
   \brief
**/
class OpLASTARG : public OperateurPile {
public:
    OpLASTARG(const QString& s) :OperateurPile(s) {}
    OpLASTARG* Clone();
    Litterale* faireOperation();
};

/**
   \class OpCLEAR
   \brief
**/
class OpCLEAR : public OperateurPile {
public:
    OpCLEAR(const QString& s) :OperateurPile(s) {}
    OpCLEAR* Clone();
    Litterale* faireOperation();
};

/**
   \class OpSTO
   \brief
**/
class OpSTO : public OperateurBinaire {
public:
    OpSTO(const QString& s) :OperateurBinaire(s) {}
    OpSTO* Clone();
    Litterale* faireOperation();
};

/**
   \class OpFORGET
   \brief
**/
class OpFORGET : public OperateurUnaire {
public:
    OpFORGET(const QString& s) :OperateurUnaire(s) {}
    OpFORGET* Clone();
    Litterale* faireOperation();
};

/**
   \class OpIFT
   \brief
**/
class OpIFT : public OperateurBinaire {
public:
    OpIFT(const QString& s) :OperateurBinaire(s) {}
    OpIFT* Clone();
    Litterale* faireOperation();
};

/**
   \class FabriqueOperateur
   \brief
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

bool isOperateur(const QString& s);

OperateurBinaire* OperateurToOpBin(Operateur* Op);
OperateurUnaire* OperateurToOpUn(Operateur* Op);
OperateurPile* OperateurToOpPile(Operateur* Op);
#endif
