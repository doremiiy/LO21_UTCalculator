
#include "litterale.h"
#include "Operateur.h"

Entier * Entier::Clone() const
{
    return new Entier(*this);
}

QString Entier::toString() const
{
    return QString::number(value);
}

bool isEntier(const QString & s)
{
    QRegExp r("^-?[\\d]+$");
    return s.contains(r);
}

Reel * Reel::Clone() const
{
    return new Reel(*this);
}

QString Reel::toString() const
{
    return QString::number(value);
}

bool isReel(const QString & s)
{
    QRegExp r("^(-?[\\d]*\\.[\\d]+)|(-?[\\d]+\\.[\\d]*)$");
    return s.contains(r);
}

bool isAtome(const QString & s)
{
    QRegExp r("^[A-Z]([A-Z]|[0-9])*$");
    return s.contains(r);
}

bool isExpression(const QString & s)
{
    unsigned int nbParGauche = 0;
    unsigned int nbParDroite = 0;
    for (unsigned int i = 0; i < s.length(); i++) {
        if (s[i] == '(')
            nbParGauche++;
        if (s[i] == ')')
            nbParDroite++;
    }
    if (nbParDroite != nbParGauche)return false;
    QRegExp r("^'([A-Z0-9\\(\\)\\$\\+\\*/-,])+'$");
    return s.contains(r);
}

const QString supprimerEspacesExpression(const QString & s)
{
    QString sSansEsp;
    for (unsigned int i = 0; i < s.length(); i++) {
        if (s[i] != ' ')
            sSansEsp += s[i];
    }
    return sSansEsp;
}

const QString supprimerGuillemetsExpression(const QString & s)
{
    QString sSansGuillemet;
    for (unsigned int i = 0; i < s.length(); i++) {
        if (s[i] != '\'')
            sSansGuillemet += s[i];
    }
    return sSansGuillemet;
}

const QString supprimerParentheseExpression(const QString& s){
    QString sSansPar;
    for (unsigned int i = 0; i < s.length(); i++) {
        if (s[i] != '(' && s[i]!=')')
            sSansPar += s[i];
    }
    return sSansPar;
}

bool isProgramme(const QString & s)
{
    //A Completer
    return false;
}

Rationnel * Rationnel::Clone() const
{
    return new Rationnel(*this);
}

QString Rationnel::toString() const
{
    QString s;
    s=s+QString::number(numerateur);
    s=s+"/";
    s=s+QString::number(denominateur);
    return s;
}

bool isRationnel(const QString & s)
{
    QRegExp r("^(-?[\\d]+)(\\/([\\d]+))$");
     return s.contains(r);
}

void Rationnel::simplifier()
{
    if (denominateur == 0) throw LitteraleException("Erreur : Dénominateur nul");
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

QString Complexe::toString() const
{
    QString s;
    s=s+QString(pRe->toString());
    s=s+"$";
    s=s+QString(pIm->toString());
    return s;
}

QString Atome::toString() const
{
    return identificateur;
}

bool isComplexe(const QString & s)
{
    unsigned int i, pos=(unsigned int) s.length();
    for (i = 0; i < (unsigned int) s.length(); i++) {
        if (s[i] == '$') pos = i;
    }
    if (pos == (unsigned int) s.length()) return false;
    return (isLitteraleNumeric(s.leftRef(pos).toString()) && isLitteraleNumeric(s.rightRef(pos + 1).toString()));
}

bool isLitteraleNumeric(const QString& s)
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

bool isLitterale(const QString& s)
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
    QVector<Litterale*>::iterator It;
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
    QVector<Litterale*>::const_iterator It = LitTab.begin();
    unsigned int i = 0;
    while (It != LitTab.end() && *It != l) {
        ++It;
        i++;
    }
    if (i == (unsigned int)LitTab.size()) throw LitteraleException("Element inconnu");
    /*if (LitToComp(l) != nullptr) {
        supprimer(LitToComp(l)->getPReel());
        supprimer(LitToComp(l)->getPIm());
    }*/
    LitTab.erase(LitTab.begin() + i);
    //delete l;
}

Litterale * FabriqueLitterale::fabriquerLitterale(const QString & s)
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
    if (isExpression(s)) {
        L=fabriquerExpression(s);
        return L;
    }
    throw LitteraleException("Erreur : pas de litterale correspondant");
}

Atome * FabriqueLitterale::fabriquerAtome(const QString & s)
{
    Atome* a = new Atome(s);
    LitTab.push_back(a);
    return a;
}

Expression * FabriqueLitterale::fabriquerExpression(const QString & s)
{
    QString sTmp = supprimerEspacesExpression(s);
    Expression* e = new Expression(sTmp);
    LitTab.push_back(e);
    return e;
}

QString Expression::toString() const
{
    QString sTmp = supprimerEspacesExpression(value);
    return sTmp;
}

Litterale * FabriqueLitterale::fabriquerLitterale(Litterale & l)
{
    Litterale* tL = l.Clone();
    LitTab.push_back(tL);
    return &l;
}

LitteraleNumeric * FabriqueLitterale::fabriquerLitNum(const QString & s)
{
    if (isEntier(s)) {
        Entier* e = new Entier(s.toInt());
        LitTab.push_back(e);
        return e;
    }
    if (isReel(s)) {
        Reel* e = new Reel(s.toDouble());
        LitTab.push_back(e);
        return e;
    }
    if (isRationnel(s)) {
        return fabriquer/*Rationnel*/(NumerateurFromStr(s), DenominateurFromStr(s));
    }
}

Litterale * FabriqueLitterale::fabriquerComplexe(const QString & s)
{
    unsigned int i, pos = s.length();
    for(i=0;i<s.length();i++){
        if (s[i] == '$') pos = i;
    }
    if (pos == s.length()) throw LitteraleException("Erreur");
    if (pos != s.length()) {
        LitteraleNumeric* pRe = fabriquerLitNum(s.rightRef(pos).toString());
        LitteraleNumeric* pIm = fabriquerLitNum(s.leftRef(pos + 1).toString());
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

int NumerateurFromStr(const QString & s)
{
    if (isRationnel(s)) {
        unsigned int i = 0;
        while (s[i] != '/') i++;
        return s.rightRef(i).toInt();
    }
}

int DenominateurFromStr(const QString & s)
{
    if (isRationnel(s)) {
        unsigned int i = 0;
        while (s[i] != '/') i++;
        return s.leftRef(i + 1).toInt();
    }
}


Expression * Expression::Clone() const
{
    return new Expression(*this);
}

QString Programme::toString() const
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

bool LitteraleNumeric::LitteraleNumeriqueNulle(LitteraleNumeric * ln) const
{
    if (LitNumToEnt(ln) != nullptr) {
        if (LitNumToEnt(ln)->getValue() == 0)
            return true;
        return false;
    }
    if (LitNumToRat(ln) != nullptr) {
        if (LitNumToRat(ln)->getNumerateur() == 0)
            return true;
        return false;
    }
    if (LitNumToReel(ln) != nullptr) {
        if (LitNumToReel(ln)->getValue() == 0)
            return true;
        return false;
    }
    throw LitteraleException("Erreur");
}

Litterale* Expression::eval() const {
    FabriqueLitterale& f=FabriqueLitterale::getInstance();
    FabriqueOperateur& o=FabriqueOperateur::getInstance();
    Controleur& c=Controleur::getInstance();
    //QHash<QString,LitteraleNumeric*> v=c.getVar();
    QString exp=value;
    QString s=supprimerGuillemetsExpression(exp);
    if(isLitterale(s)){
        if(!isAtome(s)){
            Litterale* res=f.fabriquerLitterale(s);
            return res;
        }
        else{
            QHash<QString,LitteraleNumeric*>::iterator It=c.Var.find(s);
            if(It!=c.Var.end()){
                return It.value();
            }
            else
                throw OperateurException("Erreur : nom de variable inconnu");
        }
    }

    //Evaluation des operateurs binaires
    QRegExp r2("([A-Z](?:[A-Z])*)\\((.+),(.+)\\)");
    while(r2.indexIn(s)>-1){
        QString op=r2.cap(1);
        QString arg1=r2.cap(2);
        QString arg2=r2.cap(3);
        Expression* argTmp1=f.fabriquerExpression(arg1);
        Litterale* resTmp1=argTmp1->eval();
        Expression* argTmp2=f.fabriquerExpression(arg2);
        Litterale* resTmp2=argTmp2->eval();
        OperateurBinaire* TmpOp=OperateurToOpBin(o.fabriquer(op));
        TmpOp->putLitterale(resTmp1,resTmp2);
        Litterale* res=TmpOp->faireOperation(); //Ajouter un bloc try/catch
        s.replace(s.indexOf(op),3+op.length()+arg1.length()+arg2.length(),res->toString());
        Expression* ss=f.fabriquerExpression(s);
        return ss->eval();
    }

    //Evaluation des operateurs unaires
    QRegExp r1("([A-Z](?:[A-Z])*)\\(([^,]+)\\)");
    while(r1.indexIn(s)>-1){
        QString op=r1.cap(1);
        QString arg=r1.cap(2);
        Expression* argTmp=f.fabriquerExpression(arg);
        Litterale* resTmp=argTmp->eval();
        OperateurUnaire* TmpOp2=OperateurToOpUn(o.fabriquer(op));
        TmpOp2->putLitterale(resTmp);
        Litterale* res=TmpOp2->faireOperation(); //Ajouter un bloc try/catch
        s.replace(s.indexOf(op),2+op.length()+arg.length(),res->toString());
        Expression* ss=f.fabriquerExpression(s);
        return ss->eval();
    }


    //Evaluation globale par rapport aux parentheses
    QRegExp r3("(\\([^\\(]*\\))");
    while(r3.indexIn(s)>-1){
        QString arg1=r3.cap(1);
        QString arg=supprimerParentheseExpression(r3.cap(1));
        Expression* argTmp=f.fabriquerExpression(arg);
        Litterale* res=argTmp->eval();
        s.replace(s.indexOf(r3.cap(1)),r3.cap(1).length(),res->toString());
        Expression* ss=f.fabriquerExpression(s);
        return ss->eval();
    }

    //Evaluation * /
    QRegExp r4("(-?[0-9]+|([A-Z]([A-Z]|[0-9])*))([\\*/])(-?[0-9]+|([A-Z]([A-Z]|[0-9])*))");
    while(r4.indexIn(s)>-1){
        QString arg1=r4.cap(1);
        QString op=r4.cap(4);
        QString arg2=r4.cap(5);
        Expression* argTmp1=f.fabriquerExpression(arg1);
        Litterale* resTmp1=argTmp1->eval();
        Expression* argTmp2=f.fabriquerExpression(arg2);
        Litterale* resTmp2=argTmp2->eval();
        OperateurBinaire* OpTmp=OperateurToOpBin(o.fabriquer(op));
        OpTmp->putLitterale(resTmp1,resTmp2);
        Litterale* res=OpTmp->faireOperation(); //Ajouter un bloc try/catch
        s.replace(s.indexOf(arg1),op.length()+arg1.length()+arg2.length(),res->toString());
        Expression* ss=f.fabriquerExpression(s);
        return ss->eval();
    }

    //Evaluation + -
    QRegExp r5("(-?[0-9]+|([A-Z]([A-Z]|[0-9])*))([\\+-])(-?[0-9]+|([A-Z]([A-Z]|[0-9])*))");
    while(r5.indexIn(s)>-1){
        QString arg1=r5.cap(1);
        QString op=r5.cap(4);
        QString arg2=r5.cap(5);
        Expression* argTmp1=f.fabriquerExpression(arg1);
        Litterale* resTmp1=argTmp1->eval();
        Expression* argTmp2=f.fabriquerExpression(arg2);
        Litterale* resTmp2=argTmp2->eval();
        OperateurBinaire* OpTmp=OperateurToOpBin(o.fabriquer(op));
        OpTmp->putLitterale(resTmp1,resTmp2);
        Litterale* res=OpTmp->faireOperation(); //Ajouter un bloc try/catch
        s.replace(s.indexOf(arg1),op.length()+arg1.length()+arg2.length(),res->toString());
        Expression* ss=f.fabriquerExpression(s);
        return ss->eval();
    }

}
