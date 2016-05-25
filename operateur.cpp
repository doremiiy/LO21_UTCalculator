
#include "Operateur.h"
#include "Pile.h"

const map<QString, unsigned int> Operateur::listeOperateurs = { {"+",2},{"-",2},{"*",2},{"/",2},{"NEG",1},{"DUP",1},{"DROP",1},{"SWAP",2},{"=",2},{"!=",2},{"<=",2},{">=",2},{"<",2},{">",2},{"AND",2},{"OR",2},{"NOT",1},{"NUM",1},{"DEN",1},{"$",2},{"RE",2},{"IM",2} };

unsigned int OperateurBinaire::arite = 2;
unsigned int OperateurUnaire::arite = 1;
unsigned int OperateurPile::arite = 0;

bool isOperateur(const QString & s)
{
    map<QString, unsigned int>::const_iterator It;
    for (It = Operateur::listeOperateurs.begin(); It != Operateur::listeOperateurs.end(); ++It)
        if (s == It->first) return true;
    return false;
}

OperateurBinaire * OperateurToOpBin(Operateur * Op)
{
    return dynamic_cast<OperateurBinaire*>(Op);
}

OperateurUnaire * OperateurToOpUn(Operateur * Op)
{
    return dynamic_cast<OperateurUnaire*>(Op);
}

OperateurPile * OperateurToOpPile(Operateur * Op)
{
    return dynamic_cast<OperateurPile*>(Op);
}

FabriqueOperateur::Handler FabriqueOperateur::handler = FabriqueOperateur::Handler();

FabriqueOperateur::~FabriqueOperateur()
{
    QVector<Operateur*>::iterator It;
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
    QVector<Operateur*>::const_iterator It = OpTab.begin();
    unsigned int i = 0;
    while (It != OpTab.end() && *It != Op) {
        ++It;
        i++;
    }
    if (i == OpTab.size()) throw OperateurException("Element inconnu");
    OpTab.erase(OpTab.begin() + i);
    delete(Op);
}

Operateur * FabriqueOperateur::fabriquer(const QString & s)
{
    Operateur* Op;
    if (isOperateur(s)) {
        if (s == "+") {
            Op = new OpPlus("+");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "-") {
            Op = new OpMoins("-");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "*") {
            Op = new OpFois("*");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "/") {
            Op = new OpDiviser("/");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "NEG") {
            Op = new OpNEG("NEG");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "DUP") {
            Op = new OpDUP("DUP");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "DROP") {
            Op = new OpDROP("DROP");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "SWAP") {
            Op = new OpSWAP("SWAP");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "=") {
            Op = new OpEGAL("EGAL");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "!=") {
            Op = new OpDIF("DIF");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "<") {
            Op = new OpSTRICTINF("STRICTINF");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == ">") {
            Op = new OpSTRICTSUP("STRICTSUP");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "<=") {
            Op = new OpINF("INF");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == ">=") {
            Op = new OpSUP("SUP");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "AND") {
            Op = new OpAND("AND");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "OR") {
            Op = new OpOR("OR");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "NOT") {
            Op = new OpNOT("NOT");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "NUM") {
            Op = new OpNUM("NUM");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "DEN") {
            Op = new OpDEN("DEN");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "$") {
            Op = new OpDOLLAR("$");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "RE") {
            Op = new OpRE("RE");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "IM") {
            Op = new OpIM("IM");
            OpTab.push_back(Op);
            return Op;
        }
    }
    throw OperateurException("Erreur : Operateur non reconnu");
}


void OperateurBinaire::putLitterale(Litterale * L1, Litterale * L2)
{
    l1 = L1->Clone();
    l2 = L2->Clone();
}

void OperateurUnaire::putLitterale(Litterale * L)
{
    l = L->Clone();
}

OpPlus * OpPlus::Clone()
{
    return new OpPlus(*this);
}

OpMoins * OpMoins::Clone()
{
    return new OpMoins(*this);
}

OpFois * OpFois::Clone()
{
    return new OpFois(*this);
}

OpDiviser * OpDiviser::Clone()
{
    return new OpDiviser(*this);
}

OpNEG * OpNEG::Clone()
{
    return new OpNEG(*this);
}

Litterale * OpPlus::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l1 = getLitterale1();
    Litterale* l2 = getLitterale2();
    Litterale* res;
    if (LitToEnt(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToEnt(l1)->getValue() + LitToEnt(l2)->getValue());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer((LitToRat(l2)->getDenominateur()*LitToEnt(l1)->getValue()) + LitToRat(l2)->getNumerateur(), LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToEnt(l1)->getValue() + LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            Operateur* Tmp = f2.fabriquer("+");
            OperateurBinaire* tmp = OperateurToOpBin(Tmp);
            tmp->putLitterale(l1, LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
    }
    //si l1 est rationnel
    if (LitToRat(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur() + LitToEnt(l2)->getValue()*LitToRat(l1)->getDenominateur(), LitToRat(l1)->getDenominateur());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur()*LitToRat(l2)->getDenominateur() + LitToRat(l1)->getDenominateur()*LitToRat(l2)->getNumerateur(), LitToRat(l1)->getDenominateur()*LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur() + LitToReel(l2)->getValue()*LitToRat(l1)->getDenominateur(), LitToRat(l1)->getDenominateur());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            Operateur* Tmp = f2.fabriquer("+");
            OperateurBinaire* tmp = OperateurToOpBin(Tmp);
            tmp->putLitterale(l1, LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
    }
    //si l1 est reel
    if (LitToReel(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() + LitToEnt(l2)->getValue());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer((LitToRat(l2)->getDenominateur()*LitToReel(l1)->getValue()) + LitToRat(l2)->getNumerateur(), LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() + LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            Operateur* Tmp = f2.fabriquer("+");
            OperateurBinaire* tmp = OperateurToOpBin(Tmp);
            tmp->putLitterale(l1, LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
    }
    //si l1 est complexe
    if (LitToComp(l1) != nullptr) {
        Operateur* Tmp = f2.fabriquer("+");
        OperateurBinaire* tmp = OperateurToOpBin(Tmp);
        if (LitToEnt(l2) != nullptr) {
            tmp->putLitterale(l2, LitToComp(l1)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l1)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            tmp->putLitterale(l2, LitToComp(l1)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l1)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            tmp->putLitterale(l2, LitToComp(l1)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l1)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            tmp->putLitterale(LitToComp(l2)->getPReel(), LitToComp(l1)->getPReel());
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToComp(l2)->getPIm(), LitToComp(l1)->getPIm());
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re),LitToLitNum(im));
            f2.supprimer(Tmp);
            return res;
        }
    }
    throw OperateurException("L'operateur + ne s'applique pas sur ces litterales");
}

Litterale * OpMoins::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l1 = getLitterale1();
    Litterale* l2 = getLitterale2();
    Litterale* res;
    if (LitToEnt(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToEnt(l1)->getValue() - LitToEnt(l2)->getValue());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer((LitToRat(l2)->getDenominateur()*LitToEnt(l1)->getValue()) - LitToRat(l2)->getNumerateur(), LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToEnt(l1)->getValue() - LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            Operateur* Tmp = f2.fabriquer("-");
            OperateurBinaire* tmp = OperateurToOpBin(Tmp);
            tmp->putLitterale(l1, LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
    }
    //si l1 est rationnel
    if (LitToRat(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur() - LitToEnt(l2)->getValue()*LitToRat(l1)->getDenominateur(), LitToRat(l1)->getDenominateur());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur()*LitToRat(l2)->getDenominateur() - LitToRat(l1)->getDenominateur()*LitToRat(l2)->getNumerateur(), LitToRat(l1)->getDenominateur()*LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur() - LitToReel(l2)->getValue()*LitToRat(l1)->getDenominateur(), LitToRat(l1)->getDenominateur());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            Operateur* Tmp = f2.fabriquer("-");
            OperateurBinaire* tmp = OperateurToOpBin(Tmp);
            tmp->putLitterale(l1, LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
    }
    //si l1 est reel
    if (LitToReel(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() - LitToEnt(l2)->getValue());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer((LitToRat(l2)->getDenominateur()*LitToReel(l1)->getValue()) - LitToRat(l2)->getNumerateur(), LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() - LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            Operateur* Tmp = f2.fabriquer("-");
            OperateurBinaire* tmp = OperateurToOpBin(Tmp);
            tmp->putLitterale(l1, LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
    }
    //si l1 est complexe
    if (LitToComp(l1) != nullptr) {
        Operateur* Tmp = f2.fabriquer("-");
        OperateurBinaire* tmp = OperateurToOpBin(Tmp);
        if (LitToEnt(l2) != nullptr) {
            tmp->putLitterale(l2, LitToComp(l1)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l1)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            tmp->putLitterale(l2, LitToComp(l1)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l1)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            tmp->putLitterale(l2, LitToComp(l1)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l1)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            tmp->putLitterale(LitToComp(l2)->getPReel(), LitToComp(l1)->getPReel());
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToComp(l2)->getPIm(), LitToComp(l1)->getPIm());
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(Tmp);
            return res;
        }
    }
    throw OperateurException("L'operateur + ne s'applique pas sur ces litterales");
}

Litterale * OpFois::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l1 = getLitterale1();
    Litterale* l2 = getLitterale2();
    Litterale* res;
    if (LitToEnt(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToEnt(l1)->getValue() * LitToEnt(l2)->getValue());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(LitToEnt(l1)->getValue() * LitToRat(l2)->getNumerateur(), LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToEnt(l1)->getValue() * LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            Operateur* Tmp = f2.fabriquer("*");
            OperateurBinaire* tmp = OperateurToOpBin(Tmp);
            tmp->putLitterale(l1, LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
    }
    //si l1 est rationnel
    if (LitToRat(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur() * LitToEnt(l2)->getValue(), LitToRat(l1)->getDenominateur());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur()*LitToRat(l2)->getNumerateur(), LitToRat(l1)->getDenominateur()*LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur() * LitToReel(l2)->getValue(), LitToRat(l1)->getDenominateur());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            Operateur* Tmp = f2.fabriquer("*");
            OperateurBinaire* tmp = OperateurToOpBin(Tmp);
            tmp->putLitterale(l1, LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
    }
    //si l1 est reel
    if (LitToReel(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() * LitToEnt(l2)->getValue());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() * LitToRat(l2)->getNumerateur(), LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() * LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            Operateur* Tmp = f2.fabriquer("*");
            OperateurBinaire* tmp = OperateurToOpBin(Tmp);
            tmp->putLitterale(l1, LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
    }
    //si l1 est complexe
    if (LitToComp(l1) != nullptr) {
        Operateur* Tmp = f2.fabriquer("*");
        OperateurBinaire* tmp = OperateurToOpBin(Tmp);
        if (LitToEnt(l2) != nullptr) {
            tmp->putLitterale(LitToEnt(l2), LitToComp(l1)->getPReel());
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToEnt(l2), LitToComp(l1)->getPIm());
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(Tmp);
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            tmp->putLitterale(LitToRat(l2), LitToComp(l1)->getPReel());
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToRat(l2), LitToComp(l1)->getPIm());
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(Tmp);
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            tmp->putLitterale(LitToReel(l2), LitToComp(l1)->getPReel());
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToReel(l2), LitToComp(l1)->getPIm());
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(Tmp);
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            Operateur* Tmp2 = f2.fabriquer("-");
            OperateurBinaire* tmp2 = OperateurToOpBin(Tmp2);
            Operateur* Tmp3 = f2.fabriquer("+");
            OperateurBinaire* tmp3 = OperateurToOpBin(Tmp3);

            tmp->putLitterale(LitToComp(l2)->getPReel(), LitToComp(l1)->getPReel());
            Litterale* reTmp = tmp->faireOperation();//a*a'
            tmp->putLitterale(LitToComp(l2)->getPIm(), LitToComp(l1)->getPIm());
            Litterale* imTmp = tmp->faireOperation();//b*b'
            tmp2->putLitterale(reTmp,imTmp);
            Litterale* re = tmp2->faireOperation();//aa'-bb'
            tmp3->putLitterale(reTmp,imTmp);
            Litterale* im = tmp3->faireOperation();//aa'+bb'

            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(Tmp);
            f2.supprimer(Tmp2);
            f2.supprimer(Tmp3);
            return res;
        }
    }
    throw OperateurException("L'operateur + ne s'applique pas sur ces litterales");
}

Litterale * OpDiviser::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l1 = getLitterale1();
    Litterale* l2 = getLitterale2();
    Litterale* res;
    if (LitToEnt(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToEnt(l1)->getValue() / LitToEnt(l2)->getValue());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(LitToEnt(l1)->getValue()*LitToRat(l2)->getDenominateur(), LitToRat(l2)->getNumerateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToEnt(l1)->getValue() / LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            Operateur* Tmp = f2.fabriquer("/");
            OperateurBinaire* tmp = OperateurToOpBin(Tmp);
            tmp->putLitterale(l1, LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
    }
    //si l1 est rationnel
    if (LitToRat(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur(),LitToRat(l1)->getDenominateur()*LitToEnt(l1)->getValue());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur()*LitToRat(l2)->getDenominateur(), LitToRat(l1)->getDenominateur()*LitToRat(l2)->getNumerateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur(), LitToRat(l1)->getDenominateur()*LitToReel(l1)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            Operateur* Tmp = f2.fabriquer("/");
            OperateurBinaire* tmp = OperateurToOpBin(Tmp);
            tmp->putLitterale(l1, LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
    }
    //si l1 est reel
    if (LitToReel(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() / LitToEnt(l2)->getValue());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue()*LitToRat(l2)->getDenominateur(),LitToRat(l2)->getNumerateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() / LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            Operateur* Tmp = f2.fabriquer("/");
            OperateurBinaire* tmp = OperateurToOpBin(Tmp);
            tmp->putLitterale(l1, LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(Tmp);
            return res;
        }
    }
    //si l1 est complexe
    if (LitToComp(l1) != nullptr) {
        Operateur* Tmp = f2.fabriquer("/");
        OperateurBinaire* tmp = OperateurToOpBin(Tmp);
        if (LitToEnt(l2) != nullptr) {
            tmp->putLitterale(LitToEnt(l2), LitToComp(l1)->getPReel());
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToEnt(l2), LitToComp(l1)->getPIm());
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(Tmp);
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            tmp->putLitterale(LitToRat(l2), LitToComp(l1)->getPReel());
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToRat(l2), LitToComp(l1)->getPIm());
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(Tmp);
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            tmp->putLitterale(LitToReel(l2), LitToComp(l1)->getPReel());
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToReel(l2), LitToComp(l1)->getPIm());
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(Tmp);
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            Operateur* Tmp1 = f2.fabriquer("*");
            OperateurBinaire* tmp1 = OperateurToOpBin(Tmp1);
            Operateur* Tmp2 = f2.fabriquer("-");
            OperateurBinaire* tmp2 = OperateurToOpBin(Tmp2);
            Operateur* Tmp3 = f2.fabriquer("+");
            OperateurBinaire* tmp3 = OperateurToOpBin(Tmp3);

            tmp1->putLitterale(LitToComp(l2)->getPReel(), LitToComp(l1)->getPReel());
            Litterale* reTmp1 = tmp1->faireOperation();//a*a'
            tmp1->putLitterale(LitToComp(l2)->getPIm(), LitToComp(l1)->getPIm());
            Litterale* reTmp2 = tmp1->faireOperation();//b*b'
            tmp1->putLitterale(LitToComp(l2)->getPReel(), LitToComp(l2)->getPReel());
            Litterale* reTmp3 = tmp1->faireOperation();//a'*a'
            tmp1->putLitterale(LitToComp(l2)->getPIm(), LitToComp(l2)->getPIm());
            Litterale* reTmp4 = tmp1->faireOperation();//b'*b'
            tmp3->putLitterale(reTmp1, reTmp2);
            Litterale* reTmp5 = tmp3->faireOperation();//aa'+bb'
            tmp3->putLitterale(reTmp3, reTmp4);
            Litterale* reTmp6 = tmp3->faireOperation();//a'a'+b'b'
            tmp->putLitterale(reTmp5, reTmp6);
            Litterale* re = tmp->faireOperation();

            tmp1->putLitterale(LitToComp(l1)->getPIm(), LitToComp(l2)->getPReel());
            Litterale* imTmp1 = tmp1->faireOperation();//b*a'
            tmp1->putLitterale(LitToComp(l1)->getPReel(), LitToComp(l2)->getPIm());
            Litterale* imTmp2 = tmp1->faireOperation();//a*b'
            tmp2->putLitterale(imTmp1, imTmp2);
            Litterale* imTmp3 = tmp2->faireOperation();//ba'-ab'
            tmp->putLitterale(imTmp3, reTmp6);
            Litterale* im = tmp->faireOperation();

            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(Tmp);
            f2.supprimer(Tmp1);
            f2.supprimer(Tmp2);
            f2.supprimer(Tmp3);
            return res;
        }
    }
    throw OperateurException("L'operateur + ne s'applique pas sur ces litterales");
}

Litterale * OpNEG::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l = getLitterale();
    Litterale* res;
    if (LitToEnt(l) != nullptr) {
        res = f1.fabriquer(LitToEnt(l)->getValue()*(-1));
        return res;
    }
    if (LitToRat(l) != nullptr) {
        res = f1.fabriquer(LitToRat(l)->getNumerateur()*(-1), LitToRat(l)->getDenominateur());
        return res;
    }
    if (LitToReel(l) != nullptr) {
        res = f1.fabriquer(LitToReel(l)->getValue()*(-1));
        return res;
    }
    if (LitToComp(l) != nullptr) {
        Operateur* Tmp = f2.fabriquer("NEG");
        OperateurToOpUn(Tmp)->putLitterale(LitToComp(l)->getPReel());
        LitteraleNumeric* re = LitToLitNum(OperateurToOpUn(Tmp)->faireOperation());
        OperateurToOpUn(Tmp)->putLitterale(LitToComp(l)->getPIm());
        LitteraleNumeric* im = LitToLitNum(OperateurToOpUn(Tmp)->faireOperation());
        res = f1.fabriquerComplexe(re, im);
        f2.supprimer(Tmp);
        return res;
    }
    throw OperateurException("Erreur : cette operateur ne s'applique pas sur ce type de litterale");
}

OpDUP * OpDUP::Clone()
{
    return new OpDUP(*this);
}

Litterale * OpDUP::faireOperation()
{
    FabriqueLitterale& f = FabriqueLitterale::getInstance();
    Litterale* res;
    Pile& p = Pile::getInstance();
    if (!p.estVide()) {
        Litterale* l = &p.top();
        res = f.fabriquerLitterale(*l);
        return res;
    }
    throw PileException("La pile est vide");
}

OpDROP * OpDROP::Clone()
{
    return new OpDROP(*this);
}

Litterale * OpDROP::faireOperation()
{
    Pile& p = Pile::getInstance();
    if (!p.estVide()) {
        p.pop();
        return nullptr;
    }
    throw PileException("La pile est vide");
}

OpSWAP * OpSWAP::Clone()
{
    return new OpSWAP(*this);
}

Litterale * OpSWAP::faireOperation()
{
    FabriqueLitterale& f = FabriqueLitterale::getInstance();
    Pile& p = Pile::getInstance();
    if (p.taille() >= 2) {
        Litterale* l1 = f.fabriquerLitterale(*(&p.top()));
        p.pop();
        Litterale* l2 = f.fabriquerLitterale(*(&p.top()));
        p.pop();
        p.push(*l1);
        p.push(*l2);
        return nullptr;
    }
    throw PileException("Impossible d'appliquer l'operateur");
}

OpEGAL * OpEGAL::Clone()
{
    return new OpEGAL(*this);
}

Litterale * OpEGAL::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l1 = getLitterale1();
    Litterale* l2 = getLitterale2();
    Litterale* res;
    if((LitToLitNum(l1) == nullptr) && (LitToLitNum(l2) == nullptr))
        throw OperateurException("Erreur : impossible d'appliquer l'operateur sur ces litterales");
    if (LitToLitNum(l1) != nullptr && LitToLitNum(l2) != nullptr) {
        Operateur* OpTmp=f2.fabriquer("-");
        OperateurBinaire* tmp = OperateurToOpBin(OpTmp);
        tmp->putLitterale(l1, l2);
        Litterale* resTmp = tmp->faireOperation();
        if (LitToLitNum(resTmp)->LitteraleNumeriquePositive(LitToLitNum(resTmp)) || LitToLitNum(resTmp)->LitteraleNumeriqueNegative(LitToLitNum(resTmp)))
            res = f1.fabriquerLitterale("0");
        else
            res = f1.fabriquerLitterale("1");
        f2.supprimer(OpTmp);
        return res;
    }
}

OpDIF * OpDIF::Clone()
{
    return new OpDIF(*this);
}

Litterale * OpDIF::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l1 = getLitterale1();
    Litterale* l2 = getLitterale2();
    Litterale* res;
    if (LitToLitNum(l1) != nullptr && LitToLitNum(l2) != nullptr) {
        Operateur* OpTmp = f2.fabriquer("-");
        OperateurBinaire* tmp = OperateurToOpBin(OpTmp);
        tmp->putLitterale(l1, l2);
        Litterale* resTmp = tmp->faireOperation();
        if (LitToLitNum(resTmp)->LitteraleNumeriquePositive(LitToLitNum(resTmp)) || LitToLitNum(resTmp)->LitteraleNumeriqueNegative(LitToLitNum(resTmp)))
            res = f1.fabriquerLitterale("1");
        else
            res = f1.fabriquerLitterale("0");
        f2.supprimer(OpTmp);
        return res;
    }
    else return nullptr;
    //throw OperateurException("Erreur : impossible d'appliquer l'operateur sur ces litterales");
}

OpSTRICTINF * OpSTRICTINF::Clone()
{
    return new OpSTRICTINF(*this);
}

Litterale * OpSTRICTINF::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l1 = getLitterale1();
    Litterale* l2 = getLitterale2();
    Litterale* res;
    if (LitToLitNum(l1) != nullptr && LitToLitNum(l2) != nullptr) {
        Operateur* OpTmp = f2.fabriquer("-");
        OperateurBinaire* tmp = OperateurToOpBin(OpTmp);
        tmp->putLitterale(l1, l2);
        Litterale* resTmp = tmp->faireOperation();
        if (LitToLitNum(resTmp)->LitteraleNumeriqueNegative(LitToLitNum(resTmp)))
            res = f1.fabriquerLitterale("1");
        else
            res = f1.fabriquerLitterale("0");
        f2.supprimer(OpTmp);
        return res;
    }
    else return nullptr;
}

OpSTRICTSUP * OpSTRICTSUP::Clone()
{
    return new OpSTRICTSUP(*this);
}

Litterale * OpSTRICTSUP::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l1 = getLitterale1();
    Litterale* l2 = getLitterale2();
    Litterale* res;
    if (LitToLitNum(l1) != nullptr && LitToLitNum(l2) != nullptr) {
        Operateur* OpTmp = f2.fabriquer("-");
        OperateurBinaire* tmp = OperateurToOpBin(OpTmp);
        tmp->putLitterale(l1, l2);
        Litterale* resTmp = tmp->faireOperation();
        if (LitToLitNum(resTmp)->LitteraleNumeriquePositive(LitToLitNum(resTmp)))
            res = f1.fabriquerLitterale("1");
        else
            res = f1.fabriquerLitterale("0");
        f2.supprimer(OpTmp);
        return res;
    }
    else return nullptr;
}

OpINF * OpINF::Clone()
{
    return new OpINF(*this);
}

Litterale * OpINF::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l1 = getLitterale1();
    Litterale* l2 = getLitterale2();
    Litterale* res;
    if (LitToLitNum(l1) != nullptr && LitToLitNum(l2) != nullptr) {
        Operateur* OpTmp1 = f2.fabriquer("=");
        OperateurBinaire* tmp1 = OperateurToOpBin(OpTmp1);
        tmp1->putLitterale(l1, l2);
        Litterale* resTmp1 = tmp1->faireOperation();

        Operateur* OpTmp2 = f2.fabriquer("<");
        OperateurBinaire* tmp2 = OperateurToOpBin(OpTmp2);
        tmp2->putLitterale(l1, l2);
        Litterale* resTmp2 = tmp2->faireOperation();

        if (LitToEnt(resTmp1)->getValue() == 1)
            res = f1.fabriquerLitterale("1");
        else
            if (LitToEnt(resTmp2)->getValue() == 1)
                res = f1.fabriquerLitterale("1");
            else
                res = f1.fabriquerLitterale("0");
        f2.supprimer(OpTmp1);
        f2.supprimer(OpTmp2);
        return res;
    }
    else return nullptr;
}

OpSUP * OpSUP::Clone()
{
    return new OpSUP(*this);
}

Litterale * OpSUP::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l1 = getLitterale1();
    Litterale* l2 = getLitterale2();
    Litterale* res;
    if (LitToLitNum(l1) != nullptr && LitToLitNum(l2) != nullptr) {
        Operateur* OpTmp1 = f2.fabriquer("=");
        OperateurBinaire* tmp1 = OperateurToOpBin(OpTmp1);
        tmp1->putLitterale(l1, l2);
        Litterale* resTmp1 = tmp1->faireOperation();

        Operateur* OpTmp2 = f2.fabriquer(">");
        OperateurBinaire* tmp2 = OperateurToOpBin(OpTmp2);
        tmp2->putLitterale(l1, l2);
        Litterale* resTmp2 = tmp2->faireOperation();

        if (LitToEnt(resTmp1)->getValue() == 1)
            res = f1.fabriquerLitterale("1");
        else
            if (LitToEnt(resTmp2)->getValue() == 1)
                res = f1.fabriquerLitterale("1");
            else
                res = f1.fabriquerLitterale("0");
        f2.supprimer(OpTmp1);
        f2.supprimer(OpTmp2);
        return res;
    }
    else return nullptr;
}

OpAND * OpAND::Clone()
{
    return new OpAND(*this);
}

Litterale * OpAND::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l1 = getLitterale1();
    Litterale* l2 = getLitterale2();
    Litterale* res;
    if (LitToLitNum(l1) != nullptr && LitToLitNum(l2) != nullptr) {
        if (!LitToLitNum(l1)->LitteraleNumeriqueNulle(LitToLitNum(l1)) && !LitToLitNum(l2)->LitteraleNumeriqueNulle(LitToLitNum(l2)))
            res = f1.fabriquerLitterale("1");
        else
            res = f1.fabriquerLitterale("0");
        return res;
    }
    else return nullptr;
}

OpOR * OpOR::Clone()
{
    return new OpOR(*this);
}

Litterale * OpOR::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l1 = getLitterale1();
    Litterale* l2 = getLitterale2();
    Litterale* res;
    if (LitToLitNum(l1) != nullptr && LitToLitNum(l2) != nullptr) {
        if (LitToLitNum(l1)->LitteraleNumeriqueNulle(LitToLitNum(l1)) && LitToLitNum(l2)->LitteraleNumeriqueNulle(LitToLitNum(l2)))
            res = f1.fabriquerLitterale("0");
        else
            res = f1.fabriquerLitterale("1");
        return res;
    }
    else return nullptr;
}

OpNOT * OpNOT::Clone()
{
    return new OpNOT(*this);
}

Litterale * OpNOT::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l = getLitterale();
    Litterale* res;
    if (LitToLitNum(l) != nullptr) {
        if (LitToLitNum(l)->LitteraleNumeriqueNulle(LitToLitNum(l)))
            res = f1.fabriquerLitterale("1");
        else
            res = f1.fabriquerLitterale("0");
        return res;
    }
    else return nullptr;
}

OpNUM * OpNUM::Clone()
{
    return new OpNUM(*this);
}

Litterale * OpNUM::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l = getLitterale();
    Litterale* res;
    if (LitToRat(l) != nullptr) {
        res = f1.fabriquer(LitToRat(l)->getNumerateur());
        return res;
    }
    if (LitToEnt(l) != nullptr) {
        res = f1.fabriquer(LitToEnt(l)->getValue());
        return res;
    }
    return nullptr;
}

OpDEN * OpDEN::Clone()
{
    return new OpDEN(*this);
}

Litterale * OpDEN::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l = getLitterale();
    Litterale* res;
    if (LitToRat(l) != nullptr) {
        res = f1.fabriquer(LitToRat(l)->getDenominateur());
        return res;
    }
    if (LitToEnt(l) != nullptr) {
        res = f1.fabriquer(1);
        return res;
    }
    return nullptr;
}

OpDOLLAR * OpDOLLAR::Clone()
{
    return new OpDOLLAR(*this);
}

Litterale * OpDOLLAR::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l1 = getLitterale1();
    Litterale* l2 = getLitterale2();
    Litterale* res;
    if (LitToLitNum(l1) != nullptr && LitToLitNum(l2) != nullptr) {
        res = f1.fabriquerComplexe(LitToLitNum(l1),LitToLitNum(l2));
        return res;
    }
    else return nullptr;
}

OpRE * OpRE::Clone()
{
    return new OpRE(*this);
}

Litterale * OpRE::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l = getLitterale();
    Litterale* res;
    if (LitToComp(l) != nullptr) {
        res = f1.fabriquerLitNum(*LitToLitNum(LitToComp(l)->getPReel()));
        return res;
    }
    if (LitToLitNum(l) != nullptr) {
        res = f1.fabriquerLitNum(*LitToLitNum(l));
        return res;
    }
    return nullptr;
}

OpIM * OpIM::Clone()
{
    return new OpIM(*this);
}

Litterale * OpIM::faireOperation()
{
    FabriqueLitterale& f1 = FabriqueLitterale::getInstance();
    FabriqueOperateur& f2 = FabriqueOperateur::getInstance();
    Litterale* l = getLitterale();
    Litterale* res;
    if (LitToComp(l) != nullptr) {
        res = f1.fabriquerLitNum(*LitToLitNum(LitToComp(l)->getPIm()));
        return res;
    }
    if (LitToLitNum(l) != nullptr) {
        res = f1.fabriquer(0);
        return res;
    }
    return nullptr;
}
