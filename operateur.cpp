
#include "Operateur.h"
#include "Pile.h"

const map<QString, unsigned int> Operateur::listeOperateurs = { {"+",2},{"-",2},{"*",2},{"/",2},{"NEG",1},{"DUP",1},{"DROP",1},{"SWAP",2},{"=",2},{"!=",2},{"<=",2},{">=",2},{"<",2},{">",2},{"AND",2},{"OR",2},{"NOT",1},{"NUM",1},{"DEN",1},{"$",2},{"RE",2},{"IM",2},{"UNDO",0},{"REDO",0},{"LASTARG",0},{"LASTOP",0},{"LASTARG",0},{"CLEAR",0},{"STO",2},{"DIV",2},{"MOD",2},{"EVAL",1} };

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
    if (i == (unsigned int)OpTab.size()) throw OperateurException("Element inconnu");
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
        if (s == "UNDO") {
            Op = new OpUNDO("UNDO");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "REDO") {
            Op = new OpREDO("REDO");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "LASTOP") {
            Op = new OpLASTOP("LASTOP");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "LASTARG") {
            Op = new OpLASTARG("LASTARG");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "CLEAR") {
            Op = new OpCLEAR("CLEAR");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "STO") {
            Op = new OpSTO("STO");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "DIV") {
            Op = new OpDIV("DIV");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "MOD") {
            Op = new OpMOD("MOD");
            OpTab.push_back(Op);
            return Op;
        }
        if (s == "EVAL") {
            Op = new OpEVAL("EVAL");
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
            res = f1.fabriquer((LitToRat(l2)->getDenominateur() * LitToEnt(l1)->getValue()) + LitToRat(l2)->getNumerateur(), LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer((double)LitToEnt(l1)->getValue() + LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("+"));
            tmp->putLitterale(LitToEnt(l1), LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(tmp);
            return res;
        }
    }
    //si l1 est rationnel
    if (LitToRat(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur() + LitToEnt(l2)->getValue() * LitToRat(l1)->getDenominateur(), LitToRat(l1)->getDenominateur());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur() * LitToRat(l2)->getDenominateur() + LitToRat(l1)->getDenominateur()*LitToRat(l2)->getNumerateur(), LitToRat(l1)->getDenominateur() * LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(((double)LitToRat(l1)->getNumerateur() + LitToReel(l2)->getValue() * (double)LitToRat(l1)->getDenominateur()) / (double)LitToRat(l1)->getDenominateur());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("+"));
            tmp->putLitterale(LitToRat(l1), LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(tmp);
            return res;
        }
    }
    //si l1 est reel
    if (LitToReel(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() + (double)LitToEnt(l2)->getValue());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(((double)LitToRat(l2)->getDenominateur() * LitToReel(l1)->getValue() + (double)LitToRat(l2)->getNumerateur()) / (double)LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() + LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("+"));
            tmp->putLitterale(LitToReel(l1), LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(tmp);
            return res;
        }
    }
    //si l1 est complexe
    if (LitToComp(l1) != nullptr) {
        OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("+"));
        if (LitToEnt(l2) != nullptr) {
            tmp->putLitterale(LitToEnt(l2), LitToComp(l1)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l1)->getPIm());
            f2.supprimer(tmp);
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            tmp->putLitterale(LitToRat(l2), LitToComp(l1)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l1)->getPIm());
            f2.supprimer(tmp);
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            tmp->putLitterale(LitToReel(l2), LitToComp(l1)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l1)->getPIm());
            f2.supprimer(tmp);
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            tmp->putLitterale(LitToComp(l2)->getPReel(), LitToComp(l1)->getPReel());
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToComp(l2)->getPIm(), LitToComp(l1)->getPIm());
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re),LitToLitNum(im));
            f2.supprimer(tmp);
            return res;
        }
    }
    if(LitToExpression(l1)!=nullptr && LitToExpression(l2)!=nullptr){
        QString exp1=supprimerGuillemetsExpression(LitToExpression(l1)->toString());
        QString exp2=supprimerGuillemetsExpression(LitToExpression(l2)->toString());
        int samePrio1=0,samePrio2=0;
        for(unsigned int i=0;i<exp1.length();i++){
            if(exp1[i]=='('){
                while(exp1[i]!=')') i++;
            }
            if(exp1[i]=='+' || exp1[i]=='-'){
                samePrio1=1;
            }
        }
        for(unsigned int i=0;i<exp2.length();i++){
            if(exp2[i]=='('){
                while(exp1[i]!=')') i++;
            }
            if(exp2[i]=='+' || exp2[i]=='-'){
                samePrio2=1;
            }
        }
        QString s="'";
        if(samePrio1==1) s+=exp1;
        else s+="("+exp1+")";
        s+="+";
        if(samePrio2==1) s+=exp2+"'";
        else s+="("+exp2+")'";
        res=f1.fabriquerExpression(s);
        return res;
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
            res = f1.fabriquer(LitToRat(l2)->getDenominateur() * LitToEnt(l1)->getValue() - LitToRat(l2)->getNumerateur(), LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer((double)LitToEnt(l1)->getValue() - LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("-"));
            tmp->putLitterale(LitToEnt(l1), LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(tmp);
            return res;
        }
    }
    //si l1 est rationnel
    if (LitToRat(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur() - LitToEnt(l2)->getValue() * LitToRat(l1)->getDenominateur(), LitToRat(l1)->getDenominateur());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur() * LitToRat(l2)->getDenominateur() - LitToRat(l1)->getDenominateur() * LitToRat(l2)->getNumerateur(), LitToRat(l1)->getDenominateur() * LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(((double)LitToRat(l1)->getNumerateur() - LitToReel(l2)->getValue() * (double)LitToRat(l1)->getDenominateur()) / (double)LitToRat(l1)->getDenominateur());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("-"));
            tmp->putLitterale(LitToReel(l1), LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(tmp);
            return res;
        }
    }
    //si l1 est reel
    if (LitToReel(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() - (double)LitToEnt(l2)->getValue());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(((double)LitToRat(l2)->getDenominateur() * LitToReel(l1)->getValue() - (double)LitToRat(l2)->getNumerateur()) / (double)LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() - LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("-"));
            tmp->putLitterale(LitToReel(l1), LitToComp(l2)->getPReel());
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l2)->getPIm());
            f2.supprimer(tmp);
            return res;
        }
    }
    //si l1 est complexe
    if (LitToComp(l1) != nullptr) {
        OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("-"));
        if (LitToEnt(l2) != nullptr) {
            tmp->putLitterale(LitToComp(l1)->getPReel(), LitToEnt(l2));
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l1)->getPIm());
            f2.supprimer(tmp);
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            tmp->putLitterale(LitToComp(l1)->getPReel(),LitToRat(l2));
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l1)->getPIm());
            f2.supprimer(tmp);
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            tmp->putLitterale(LitToComp(l1)->getPReel(),LitToReel(l2));
            res = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(res), LitToComp(l1)->getPIm());
            f2.supprimer(tmp);
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            tmp->putLitterale(LitToComp(l1)->getPReel(), LitToComp(l2)->getPReel());
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToComp(l1)->getPIm(), LitToComp(l2)->getPIm());
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(tmp);
            return res;
        }
    }
    if(LitToExpression(l1)!=nullptr && LitToExpression(l2)!=nullptr){
        QString exp1=supprimerGuillemetsExpression(LitToExpression(l1)->toString());
        QString exp2=supprimerGuillemetsExpression(LitToExpression(l2)->toString());
        int samePrio1=0,samePrio2=0;
        for(unsigned int i=0;i<exp1.length();i++){
            if(exp1[i]=='('){
                while(exp1[i]!=')') i++;
            }
            if(exp1[i]=='+' || exp1[i]=='-'){
                samePrio1=1;
            }
        }
        for(unsigned int i=0;i<exp2.length();i++){
            if(exp2[i]=='('){
                while(exp1[i]!=')') i++;
            }
            if(exp2[i]=='+' || exp2[i]=='-'){
                samePrio2=1;
            }
        }
        QString s="'";
        if(samePrio1==1) s+=exp1;
        else s+="("+exp1+")";
        s+="-";
        if(samePrio2==1) s+=exp2+"'";
        else s+="("+exp2+")'";
        res=f1.fabriquerExpression(s);
        return res;
    }
    throw OperateurException("L'operateur - ne s'applique pas sur ces litterales");
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
            res = f1.fabriquer((double)LitToEnt(l1)->getValue() * LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("*"));
            tmp->putLitterale(LitToEnt(l1), LitToComp(l2)->getPReel());
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToEnt(l1), LitToComp(l2)->getPIm());
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(tmp);
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
            res = f1.fabriquer(LitToRat(l1)->getNumerateur() * LitToRat(l2)->getNumerateur(), LitToRat(l1)->getDenominateur() * LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer((double)LitToRat(l1)->getNumerateur() * LitToReel(l2)->getValue() / (double)LitToRat(l1)->getDenominateur());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("*"));
            tmp->putLitterale(LitToRat(l1), LitToComp(l2)->getPReel());
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToRat(l1), LitToComp(l2)->getPIm());
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(tmp);
            return res;
        }
    }
    //si l1 est reel
    if (LitToReel(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() * (double)LitToEnt(l2)->getValue());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() * (double)LitToRat(l2)->getNumerateur() / (double)LitToRat(l2)->getDenominateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() * LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("*"));
            tmp->putLitterale(LitToReel(l1), LitToComp(l2)->getPReel());
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToReel(l1), LitToComp(l2)->getPIm());
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(tmp);
        }
    }
    //si l1 est complexe
    if (LitToComp(l1) != nullptr) {
        OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("*"));
        if (LitToEnt(l2) != nullptr) {
            tmp->putLitterale(LitToComp(l1)->getPReel(),LitToEnt(l2));
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToComp(l1)->getPIm(), LitToEnt(l2));
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(tmp);
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            tmp->putLitterale(LitToComp(l1)->getPReel(), LitToRat(l2));
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToComp(l1)->getPIm(),LitToRat(l2));
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(tmp);
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            tmp->putLitterale(LitToComp(l1)->getPReel(), LitToReel(l2));
            Litterale* re = tmp->faireOperation();
            tmp->putLitterale(LitToComp(l1)->getPIm(), LitToReel(l2));
            Litterale* im = tmp->faireOperation();
            res = f1.fabriquerComplexe(LitToLitNum(re), LitToLitNum(im));
            f2.supprimer(tmp);
            return res;
        }
        if (LitToComp(l2) != nullptr) {//(ac-bd)+i(ad+bc)
            OperateurBinaire* tmp2 = OperateurToOpBin(f2.fabriquer("-"));
            OperateurBinaire* tmp3 = OperateurToOpBin(f2.fabriquer("+"));

            tmp->putLitterale(LitToComp(l1)->getPReel(), LitToComp(l2)->getPReel());
            Litterale* tmpRe = tmp->faireOperation();//ac
            tmp->putLitterale(LitToComp(l1)->getPIm(), LitToComp(l2)->getPIm());
            Litterale* tmpRe2 = tmp->faireOperation();//bd
            tmp2->putLitterale(tmpRe, tmpRe2);
            Litterale* tmpRe3 = tmp2->faireOperation();//ac-bd

            tmp->putLitterale(LitToComp(l1)->getPReel(), LitToComp(l2)->getPIm());
            Litterale* tmpIm = tmp->faireOperation();//ad
            tmp->putLitterale(LitToComp(l1)->getPIm(), LitToComp(l2)->getPReel());
            Litterale* tmpIm2 = tmp->faireOperation();//bc
            tmp3->putLitterale(tmpIm, tmpIm2);
            Litterale* tmpIm3 = tmp3->faireOperation();//ad+bc

            res = f1.fabriquerComplexe(LitToLitNum(tmpRe3), LitToLitNum(tmpIm3));
            f2.supprimer(tmp);
            f2.supprimer(tmp2);
            f2.supprimer(tmp3);
            return res;
        }
    }
    if(LitToExpression(l1)!=nullptr && LitToExpression(l2)!=nullptr){
        QString exp1=supprimerGuillemetsExpression(LitToExpression(l1)->toString());
        QString exp2=supprimerGuillemetsExpression(LitToExpression(l2)->toString());
        int samePrio1=0,samePrio2=0;
        for(unsigned int i=0;i<exp1.length();i++){
            if(exp1[i]=='('){
                while(exp1[i]!=')') i++;
            }
            if(exp1[i]=='/' || exp1[i]=='*'){
                samePrio1=1;
            }
        }
        for(unsigned int i=0;i<exp2.length();i++){
            if(exp2[i]=='('){
                while(exp1[i]!=')') i++;
            }
            if(exp2[i]=='/' || exp2[i]=='*'){
                samePrio2=1;
            }
        }
        QString s="'";
        if(samePrio1==1) s+=exp1;
        else s+="("+exp1+")";
        s+="*";
        if(samePrio2==1) s+=exp2+"'";
        else s+="("+exp2+")'";
        res=f1.fabriquerExpression(s);
        return res;
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
    //l1 ENTIER
    if (LitToEnt(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToEnt(l1)->getValue(),LitToEnt(l2)->getValue());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(LitToEnt(l1)->getValue() * LitToRat(l2)->getDenominateur(), LitToRat(l2)->getNumerateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer((double)LitToEnt(l1)->getValue() / LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) { // a/(b+ic)=(ab/(b≤+c≤))-(ac/(b≤+c≤))i)
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("*"));
            OperateurBinaire* tmp2 = OperateurToOpBin(f2.fabriquer("+"));
            OperateurBinaire* tmp3 = OperateurToOpBin(f2.fabriquer("/"));
            OperateurUnaire* tmp4 = OperateurToOpUn(f2.fabriquer("NEG"));

            tmp->putLitterale(LitToComp(l2)->getPReel(), LitToComp(l2)->getPReel());
            Litterale* tmpMod = tmp->faireOperation();//b≤
            tmp->putLitterale(LitToComp(l2)->getPIm(), LitToComp(l2)->getPIm());
            Litterale* tmpMod2 = tmp->faireOperation();//c≤
            tmp2->putLitterale(tmpMod,tmpMod2);
            Litterale* tmpMod3 = tmp2->faireOperation();//b≤+c≤

            tmp->putLitterale(LitToEnt(l1), LitToComp(l2)->getPReel());
            Litterale* tmpRe = tmp->faireOperation();//ab
            tmp->putLitterale(LitToEnt(l1), LitToComp(l2)->getPIm());
            Litterale* tmpIm = tmp->faireOperation();//ac
            tmp4->putLitterale(tmpIm);
            Litterale* tmpIm2 = tmp4->faireOperation();//-ac

            tmp3->putLitterale(tmpRe, tmpMod3);
            Litterale* tmpRe2 = tmp3->faireOperation();//ab/(b≤+c≤)
            tmp3->putLitterale(tmpIm2, tmpMod3);
            Litterale* tmpIm3 = tmp3->faireOperation();//-ac/(b≤+c≤)

            res = f1.fabriquerComplexe(LitToLitNum(tmpRe2), LitToLitNum(tmpIm3));
            f2.supprimer(tmp);
            f2.supprimer(tmp2);
            f2.supprimer(tmp3);
            f2.supprimer(tmp4);
            return res;
        }
    }
    //l1 RATIONNEL
    if (LitToRat(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur(), LitToRat(l1)->getDenominateur()*LitToEnt(l2)->getValue());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(LitToRat(l1)->getNumerateur()*LitToRat(l2)->getDenominateur(), LitToRat(l1)->getDenominateur()*LitToRat(l2)->getNumerateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer((double)LitToRat(l1)->getNumerateur() / (double)LitToRat(l1)->getDenominateur()*LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("*"));
            OperateurBinaire* tmp2 = OperateurToOpBin(f2.fabriquer("+"));
            OperateurBinaire* tmp3 = OperateurToOpBin(f2.fabriquer("/"));
            OperateurUnaire* tmp4 = OperateurToOpUn(f2.fabriquer("NEG"));

            tmp->putLitterale(LitToComp(l2)->getPReel(), LitToComp(l2)->getPReel());
            Litterale* tmpMod = tmp->faireOperation();//b≤
            tmp->putLitterale(LitToComp(l2)->getPIm(), LitToComp(l2)->getPIm());
            Litterale* tmpMod2 = tmp->faireOperation();//c≤
            tmp2->putLitterale(tmpMod, tmpMod2);
            Litterale* tmpMod3 = tmp2->faireOperation();//b≤+c≤

            tmp->putLitterale(LitToRat(l1), LitToComp(l2)->getPReel());
            Litterale* tmpRe = tmp->faireOperation();
            tmp->putLitterale(LitToRat(l1), LitToComp(l2)->getPIm());
            Litterale* tmpIm = tmp->faireOperation();//ac
            tmp4->putLitterale(tmpIm);
            Litterale* tmpIm2 = tmp4->faireOperation();//-ac

            tmp3->putLitterale(tmpRe, tmpMod3);
            Litterale* tmpRe2 = tmp3->faireOperation();//ab/(b≤+c≤)
            tmp3->putLitterale(tmpIm2, tmpMod3);
            Litterale* tmpIm3 = tmp3->faireOperation();//-ac/(b≤+c≤)

            res = f1.fabriquerComplexe(LitToLitNum(tmpRe2), LitToLitNum(tmpIm3));
            f2.supprimer(tmp);
            f2.supprimer(tmp2);
            f2.supprimer(tmp3);
            f2.supprimer(tmp4);
            return res;
        }
    }
    //l1 REEL
    if (LitToReel(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() / (double)LitToEnt(l2)->getValue());
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() * (double)LitToRat(l2)->getDenominateur() / (double)LitToRat(l2)->getNumerateur());
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            res = f1.fabriquer(LitToReel(l1)->getValue() / LitToReel(l2)->getValue());
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("*"));
            OperateurBinaire* tmp2 = OperateurToOpBin(f2.fabriquer("+"));
            OperateurBinaire* tmp3 = OperateurToOpBin(f2.fabriquer("/"));
            OperateurUnaire* tmp4 = OperateurToOpUn(f2.fabriquer("NEG"));

            tmp->putLitterale(LitToComp(l2)->getPReel(), LitToComp(l2)->getPReel());
            Litterale* tmpMod = tmp->faireOperation();//b≤
            tmp->putLitterale(LitToComp(l2)->getPIm(), LitToComp(l2)->getPIm());
            Litterale* tmpMod2 = tmp->faireOperation();//c≤
            tmp2->putLitterale(tmpMod, tmpMod2);
            Litterale* tmpMod3 = tmp2->faireOperation();//b≤+c≤

            tmp->putLitterale(LitToReel(l1), LitToComp(l2)->getPReel());
            Litterale* tmpRe = tmp->faireOperation();
            tmp->putLitterale(LitToReel(l1), LitToComp(l2)->getPIm());
            Litterale* tmpIm = tmp->faireOperation();//ac
            tmp4->putLitterale(tmpIm);
            Litterale* tmpIm2 = tmp4->faireOperation();//-ac

            tmp3->putLitterale(tmpRe, tmpMod3);
            Litterale* tmpRe2 = tmp3->faireOperation();//ab/(b≤+c≤)
            tmp3->putLitterale(tmpIm2, tmpMod3);
            Litterale* tmpIm3 = tmp3->faireOperation();//-ac/(b≤+c≤)

            res = f1.fabriquerComplexe(LitToLitNum(tmpRe2), LitToLitNum(tmpIm3));
            f2.supprimer(tmp);
            f2.supprimer(tmp2);
            f2.supprimer(tmp3);
            f2.supprimer(tmp4);
            return res;
        }
    }
    //l1 COMPLEXE
    if (LitToComp(l1) != nullptr) {
        if (LitToEnt(l2) != nullptr) {
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("/"));
            tmp->putLitterale(LitToComp(l1)->getPReel(), LitToEnt(l2));
            Litterale* tmpRe = tmp->faireOperation();
            tmp->putLitterale(LitToComp(l1)->getPIm(), LitToEnt(l2));
            Litterale* tmpIm = tmp->faireOperation();

            res = f1.fabriquerComplexe(LitToLitNum(tmpRe),LitToLitNum(tmpIm));
            return res;
        }
        if (LitToRat(l2) != nullptr) {
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("/"));
            tmp->putLitterale(LitToComp(l1)->getPReel(), LitToRat(l2));
            Litterale* tmpRe = tmp->faireOperation();
            tmp->putLitterale(LitToComp(l1)->getPIm(), LitToRat(l2));
            Litterale* tmpIm = tmp->faireOperation();

            res = f1.fabriquerComplexe(LitToLitNum(tmpRe), LitToLitNum(tmpIm));
            return res;
        }
        if (LitToReel(l2) != nullptr) {
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("/"));
            tmp->putLitterale(LitToComp(l1)->getPReel(), LitToReel(l2));
            Litterale* tmpRe = tmp->faireOperation();
            tmp->putLitterale(LitToComp(l1)->getPIm(), LitToReel(l2));
            Litterale* tmpIm = tmp->faireOperation();

            res = f1.fabriquerComplexe(LitToLitNum(tmpRe), LitToLitNum(tmpIm));
            return res;
        }
        if (LitToComp(l2) != nullptr) {
            OperateurBinaire* tmp = OperateurToOpBin(f2.fabriquer("*"));
            OperateurBinaire* tmp2 = OperateurToOpBin(f2.fabriquer("+"));
            OperateurBinaire* tmp3 = OperateurToOpBin(f2.fabriquer("/"));
            OperateurUnaire* tmp4 = OperateurToOpUn(f2.fabriquer("NEG"));

            tmp->putLitterale(LitToComp(l2)->getPReel(), LitToComp(l2)->getPReel());
            Litterale* tmpMod = tmp->faireOperation();//c≤
            tmp->putLitterale(LitToComp(l2)->getPIm(), LitToComp(l2)->getPIm());
            Litterale* tmpMod2 = tmp->faireOperation();//d≤
            tmp2->putLitterale(tmpMod, tmpMod2);
            Litterale* tmpMod3 = tmp2->faireOperation();//c≤+d≤

            tmp4->putLitterale(LitToComp(l2)->getPIm());
            Litterale* tmpConj = tmp4->faireOperation();//-d
            Litterale* tmpConj2 = f1.fabriquerComplexe(LitToLitNum(LitToComp(l2)->getPReel()),LitToLitNum(tmpConj));//c-id
            tmp->putLitterale(LitToComp(l1), LitToComp(tmpConj2));
            Litterale* tmpFois = tmp->faireOperation();

            tmp3->putLitterale(LitToComp(tmpFois)->getPReel(), tmpMod3);
            Litterale* tmpRe = tmp3->faireOperation();

            tmp3->putLitterale(LitToComp(tmpFois)->getPIm(), tmpMod3);
            Litterale* tmpIm = tmp3->faireOperation();

            res = f1.fabriquerComplexe(LitToLitNum(tmpRe), LitToLitNum(tmpIm));
            f2.supprimer(tmp);
            f2.supprimer(tmp2);
            f2.supprimer(tmp3);
            f2.supprimer(tmp4);
            f1.supprimer(tmpConj2);
            return res;
        }
    }
    if(LitToExpression(l1)!=nullptr && LitToExpression(l2)!=nullptr){
        QString exp1=supprimerGuillemetsExpression(LitToExpression(l1)->toString());
        QString exp2=supprimerGuillemetsExpression(LitToExpression(l2)->toString());
        int samePrio1=0,samePrio2=0;
        for(unsigned int i=0;i<exp1.length();i++){
            if(exp1[i]=='('){
                while(exp1[i]!=')') i++;
            }
            if(exp1[i]=='*' || exp1[i]=='/'){
                samePrio1=1;
            }
        }
        for(unsigned int i=0;i<exp2.length();i++){
            if(exp2[i]=='('){
                while(exp1[i]!=')') i++;
            }
            if(exp2[i]=='*' || exp2[i]=='/'){
                samePrio2=1;
            }
        }
        QString s="'";
        if(samePrio1==1) s+=exp1;
        else s+="("+exp1+")";
        s+="/";
        if(samePrio2==1) s+=exp2+"'";
        else s+="("+exp2+")'";
        res=f1.fabriquerExpression(s);
        return res;
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
    if(LitToExpression(l)!=nullptr){
        QString s="'NEG("+supprimerGuillemetsExpression(LitToExpression(l)->toString())+")'";
        res=f1.fabriquerExpression(s);
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
    Pile& p = Controleur::getInstance().getPile();
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
    Pile& p = Controleur::getInstance().getPile();
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
    Pile& p = Controleur::getInstance().getPile();
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
    if(LitToExpression(l1)!=nullptr && LitToExpression(l2)!=nullptr){
        QString s="'AND("+supprimerGuillemetsExpression(LitToExpression(l1)->toString())+","+supprimerGuillemetsExpression(LitToExpression(l2)->toString())+")'";
        res=f1.fabriquerExpression(s);
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
    if(LitToExpression(l1)!=nullptr && LitToExpression(l2)!=nullptr){
        QString s="'OR("+supprimerGuillemetsExpression(LitToExpression(l1)->toString())+","+supprimerGuillemetsExpression(LitToExpression(l2)->toString())+")'";
        res=f1.fabriquerExpression(s);
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
    if(LitToExpression(l)!=nullptr){
        QString s="'NOT("+supprimerGuillemetsExpression(LitToExpression(l)->toString())+")'";
        res=f1.fabriquerExpression(s);
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
    if(LitToExpression(l)!=nullptr){
        QString s="'NUM("+supprimerGuillemetsExpression(LitToExpression(l)->toString())+")'";
        res=f1.fabriquerExpression(s);
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
    if(LitToExpression(l)!=nullptr){
        QString s="'DEN("+supprimerGuillemetsExpression(LitToExpression(l)->toString())+")'";
        res=f1.fabriquerExpression(s);
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
    if(LitToExpression(l1)!=nullptr && LitToExpression(l2)!=nullptr){
        QString exp1=supprimerGuillemetsExpression(LitToExpression(l1)->toString());
        QString exp2=supprimerGuillemetsExpression(LitToExpression(l2)->toString());
        QString s="'("+exp1+")$("+exp2+")'";
        res=f1.fabriquerExpression(s);
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
    if(LitToExpression(l)!=nullptr){
        QString s="'RE("+supprimerGuillemetsExpression(LitToExpression(l)->toString())+")'";
        res=f1.fabriquerExpression(s);
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
    if(LitToExpression(l)!=nullptr){
        QString s="'IM("+supprimerGuillemetsExpression(LitToExpression(l)->toString())+")'";
        res=f1.fabriquerExpression(s);
        return res;
    }
    return nullptr;
}

OpUNDO * OpUNDO::Clone()
{
    return new OpUNDO(*this);
}

Litterale * OpUNDO::faireOperation()
{
    Controleur::getInstance().getPile().setState(Controleur::getInstance().getCareTaker().undo());
    return nullptr;
}

OpREDO * OpREDO::Clone()
{
    return new OpREDO(*this);
}

Litterale * OpREDO::faireOperation()
{
    Controleur::getInstance().getPile().setState(Controleur::getInstance().getCareTaker().redo());
    return nullptr;
}

OpLASTOP * OpLASTOP::Clone()
{
    return new OpLASTOP(*this);
}

Litterale * OpLASTOP::faireOperation()
{
    Controleur& C = Controleur::getInstance();
    QString s = C.getCareTaker().getDernierOpUtilise();
    if (s != "") {
        Operateur* Op = FabriqueOperateur::getInstance().fabriquer(s);
        C.appliquerOperateur(Op);
    }
    return nullptr;
}

OpLASTARG * OpLASTARG::Clone()
{
    return new OpLASTARG(*this);
}

Litterale * OpLASTARG::faireOperation()
{
    Controleur& C = Controleur::getInstance();
    QVector<Litterale*> vec = C.getCareTaker().getVecteurLits();
    while (!vec.empty()) {
        Litterale* tmp = vec.back();
        C.getPile().push(*tmp);
        vec.pop_back();
        delete tmp;
    }
    return nullptr;
}

OpCLEAR * OpCLEAR::Clone()
{
    return new OpCLEAR(*this);
}

Litterale * OpCLEAR::faireOperation()
{
    Controleur& C = Controleur::getInstance();
    C.getPile().clear();
    return nullptr;
}

OpSTO * OpSTO::Clone()
{
    return new OpSTO(*this);
}

Litterale * OpSTO::faireOperation()
{
    FabriqueLitterale& f = FabriqueLitterale::getInstance();
    Litterale* l1 = getLitterale1();
    Litterale* l2 = getLitterale2();
    if(LitToComp(l1))
        throw OperateurException ("Erreur : Impossible d'appliquer l'opérateur sur ces litterales");
    else
        if(isExpression(l2->toString())){
            if(isAtome(supprimerGuillemetsExpression(LitToExpression(l2)->toString())))
                Controleur::getInstance().addVar(supprimerGuillemetsExpression(LitToExpression(l2)->toString()),LitToLitNum(l1));
        }
    return nullptr;
}

OpDIV* OpDIV::Clone(){
    return new OpDIV(*this);
}

Litterale* OpDIV::faireOperation(){
    FabriqueLitterale& f=FabriqueLitterale::getInstance();
    Litterale* l1=getLitterale1();
    Litterale* l2=getLitterale2();
    Litterale* res;
    if(LitToEnt(l1)!=nullptr && LitToEnt(l2)!=nullptr){
        int a=LitToEnt(l1)->getValue();
        int b=LitToEnt(l2)->getValue();
        if(b==0) throw OperateurException("Erreur : Division par 0");
        if(a<0) a=-a;
        if(b<0) b=-b;
        int r=0;
        while(a>=b){
            a-=b;
            r++;
        }
        res = f.fabriquer(r);
        return res;
    }
    if(LitToExpression(l1)!=nullptr && LitToExpression(l2)!=nullptr){
        QString s="'DIV("+supprimerGuillemetsExpression(LitToExpression(l1)->toString())+","+supprimerGuillemetsExpression(LitToExpression(l2)->toString())+")'";
        res=f.fabriquerExpression(s);
        return res;
    }
    else throw OperateurException("Erreur : Operateur non disponible pour ces litterales");
}

OpMOD* OpMOD::Clone() {
    return new OpMOD(*this);
}

Litterale* OpMOD::faireOperation(){
    FabriqueLitterale& f=FabriqueLitterale::getInstance();
    Litterale* l1=getLitterale1();
    Litterale* l2=getLitterale2();
    Litterale* res;
    if(LitToEnt(l1)!=nullptr && LitToEnt(l2)!=nullptr){
        int a=LitToEnt(l1)->getValue();
        int b=LitToEnt(l2)->getValue();
        if(b==0) throw OperateurException("Erreur : Division par 0");
        if(a<0) a=-a;
        if(b<0) b=-b;
        int r=0,q;
        while(a>=b){
            a-=b;
            r++;
        }
        q=a;
        res = f.fabriquer(q);
        return res;
    }
    if(LitToExpression(l1)!=nullptr && LitToExpression(l2)!=nullptr){
        QString s="'MOD("+supprimerGuillemetsExpression(LitToExpression(l1)->toString())+","+supprimerGuillemetsExpression(LitToExpression(l2)->toString())+")'";
        res=f.fabriquerExpression(s);
        return res;
    }
    else throw OperateurException("Erreur : Operateur non disponible pour ces litterales");
}

OpEVAL* OpEVAL::Clone(){
    return new OpEVAL(*this);
}

Litterale* OpEVAL::faireOperation(){
    FabriqueLitterale& f=FabriqueLitterale::getInstance();
    Litterale* l=getLitterale();
    if(LitToExpression(l)!=nullptr){
        Litterale* res=LitToExpression(l)->eval();
        //Litterale* res=f.fabriquerLitterale(LitToExpression(l)->eval()->toString());
        return res;
    }
}
