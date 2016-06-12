#include "Pile.h"
#include <QDebug>

Controleur::Handler Controleur::handler = Controleur::Handler();

Controleur& Controleur::getInstance()
{
    if (handler.instance == nullptr) handler.instance = new Controleur;
    return *handler.instance;
}

void Controleur::libererInstance()
{
    delete handler.instance;
    handler.instance = nullptr;
}

void Controleur::sauvegardeEtatPile(Operateur * op)
{
    if (op == nullptr) {
        Memento* m;
        while (!ct.VecteurRedo.empty()) {
            m = ct.VecteurRedo.back();
            ct.VecteurRedo.pop_back();
            delete m;
        }
        ct.VecteurUndo.push_back(new Memento(p.getState()));
    }
    if (op != nullptr) {
        if (op->getIdOp() != "LASTOP")
            ct.setDernierOpUtilise(op->getIdOp());
        if (op->getIdOp() == "UNDO" || op->getIdOp() == "REDO")
            ct.VecteurUndo.push_back(new Memento(p.getState()));
        else {
            Memento* m;
            while (!ct.VecteurRedo.empty()) {
                m = ct.VecteurRedo.back();
                ct.VecteurRedo.pop_back();
                delete m;
            }
            ct.VecteurUndo.push_back(new Memento(p.getState()));
        }
    }
}

void Pile::pop()
{
    if (!estVide()){
        itTab.pop_front();
        modificationEtat();
    }
    else
        throw ComputerException("Erreur : pile vide");
}

Litterale & Pile::top() const
{
    if (!estVide())
        return itTab.front()->getLitterale();
    throw ComputerException("Erreur : pile vide");
}

void Pile::push(Litterale & L)
{
    itTab.push_front(new Item(L));
    modificationEtat();
}

Memento::Memento(const QVector<Item*> items)
{
    FabriqueLitterale& f = FabriqueLitterale::getInstance();
    state = *(new QVector<Item*>);
    for (QVector<Item*>::const_iterator It = items.begin(); It != items.end(); ++It) {
        state.push_back(new Item(*f.fabriquerLitterale((*It)->getLitterale())));
    }
}

CareTaker::~CareTaker()
{
    Memento *Tmp;
    while (!VecteurUndo.empty()) {
        Tmp = VecteurUndo.back();
        VecteurUndo.pop_back();
        delete Tmp;
    }
    while (!VecteurRedo.empty()) {
        Tmp = VecteurRedo.back();
        VecteurUndo.pop_back();
        delete Tmp;
    }
}

QVector<Item*> CareTaker::undo()
{
    if (VecteurUndo.size() == 0 || VecteurUndo.size() == 1)
        throw ComputerException("Erreur impossible d'appliquer l'operateur");
    Memento* c = VecteurUndo.back();
    QVector<Item*> cState = c->getState();
    VecteurRedo.push_back(new Memento(cState));
    VecteurUndo.pop_back();
    Memento* l = VecteurUndo.back();
    QVector<Item*> lState = l->getState();
    VecteurUndo.pop_back();
    delete c;
    delete l;
    return lState;
}

QVector<Item*> CareTaker::redo()
{
    Memento* l = VecteurRedo.back();
    QVector<Item*> lState = l->getState();
    VecteurRedo.pop_back();
    delete l;
    return lState;
}

void Controleur::commande(const QString & text)
{
    QString sTmp=text;
    unsigned int nbCrochetGauche=0,nbCrochetDroit=0,nbParGauche=0,nbParDroite=0;
    for(int i=0;i<sTmp.size();i++){
        if(sTmp[i]=='[') nbCrochetGauche++;
        if(sTmp[i]==']') nbCrochetDroit++;
        if(sTmp[i]=='(') nbParGauche++;
        if(sTmp[i]==')') nbParDroite++;
    }
    if((nbCrochetGauche != nbCrochetDroit) || (nbParGauche != nbParDroite))
        throw ComputerException("Erreur : impossible de lire l'instruction");


    QString tmpExp="";
    int pos,size;
    for(int i=0;i<sTmp.size();i++){
        if(sTmp[i]=='\''){
            i++;
            pos=i;
            while(sTmp[i] != '\''){
                tmpExp+=sTmp[i];
                i++;
            }
        }
        size=tmpExp.size();
        tmpExp = supprimerEspacesExpression(tmpExp);
        sTmp.replace(pos,size,tmpExp);
    }

    int in=0;
    QString operande;
    QVector<QString> listOperande;
    for(int i=0;i<sTmp.size();i++){
        if(sTmp[i]=='['){
            in=1;
            i++;
            while(in!=0){
                if(in==1 && sTmp[i]!=' ' && sTmp[i]!='[' && sTmp[i]!=']'){
                    operande.clear();
                    while(sTmp[i]!=' ' && sTmp[i]!=']'){
                        operande+=sTmp[i];
                        i++;
                    }
                    listOperande.push_back(operande);
                }
                if(in>1){
                    operande.clear();
                    while(in!=1){
                        operande+=sTmp[i];
                        i++;
                        if(sTmp[i]=='[') in++;
                        if(sTmp[i]==']') in--;
                    }
                    operande="["+operande+"]";
                    listOperande.push_back(operande);
                    i++;
                }
                if(sTmp[i]=='[') in++;
                if(sTmp[i]==']') in--;
                i++;
            }
        }
        else
            if(sTmp[i]!=' ' && sTmp[i]!='\0'){
            operande.clear();
            while(sTmp[i]!=' ' && sTmp[i]!='\0'){
                operande+=sTmp[i];
                i++;
            }
            listOperande.push_back(operande);
        }
    }
    QVector<QString>::iterator It;

    FabriqueLitterale& f = FabriqueLitterale::getInstance();
    FabriqueOperateur& o = FabriqueOperateur::getInstance();

    for(It=listOperande.begin();It!=listOperande.end();++It){
        QString s=*It;
        if (isOperateur(s)) {
            Operateur* Op = o.fabriquer(s);
            sauvegardeEtatPile(Op);
            appliquerOperateur(Op);
            o.supprimer(Op);
        }
        else {
            if (isLitterale(s)) {
                sauvegardeEtatPile(nullptr);
                if(isAtome(s)){
                    QHash<QString,LitteraleNumeric*>::iterator It=Var.find(s);
                    QHash<QString,Programme*>::iterator It2=Progs.find(s);
                    if(It==Var.end() && It2==Progs.end()){
                        QString stmp="'"+s+"'";
                        Litterale* l=f.fabriquerExpression(stmp);
                        p.push(*l);
                        f.supprimer(l);
                    }
                    if(It!=Var.end()){
                        p.push(*It.value());
                    }
                    if(It2!=Progs.end()){
                        p.push(*It2.value());
                        Operateur* Op = o.fabriquer("EVAL");
                        appliquerOperateur(Op);
                        o.supprimer(Op);
                    }
                }
                else
                    if(isProgramme(s)){
                        Programme* l=f.fabriquerProgramme(s);
                        p.push(*l);
                        f.supprimer(l);
                    }
                    else {
                        Litterale* l = f.fabriquerLitterale(s);
                        p.push(*l);
                        f.supprimer(l);
                    }
                }
                else throw ComputerException("Erreur: Caractères non reconnu");
        }
    }
}

void Controleur::appliquerOperateur(Operateur * Op)
{
    //FabriqueLitterale& f = FabriqueLitterale::getInstance();
    FabriqueOperateur& o = FabriqueOperateur::getInstance();
    Controleur& C = Controleur::getInstance();
    if (OperateurToOpBin(Op) != nullptr) {
        qDebug()<<p.taille();
        if (p.taille() < OperateurToOpBin(Op)->getArite()) {
            o.supprimer(Op);
            throw OperateurException("Erreur : Pas assez d'arguments");
        }
        Litterale* l1 = &p.top();
        p.pop();
        if(LitToProgramme(l1)!=nullptr)
            if(Op->getIdOp()!="STO" && Op->getIdOp()!="IFT"){//empeche l'evaluation si l'operateur est STO
                LitToProgramme(l1)->eval();
                l1=&p.top();
                p.pop();
            }
        Litterale* l2 = &p.top();
        p.pop();
        if(LitToProgramme(l2)!=nullptr)
            if(Op->getIdOp()!="STO" && Op->getIdOp()!="IFT"){
                LitToProgramme(l2)->eval();
                l2=&p.top();
                p.pop();
            }
        try {
            OperateurToOpBin(Op)->putLitterale(l2, l1);
            Litterale* res = Op->faireOperation();
            C.getCareTaker().clearVecteurLits();
            C.getCareTaker().addLitteraleVecteur(l1);
            C.getCareTaker().addLitteraleVecteur(l2);
            if(Op->getIdOp()!="STO"){
                if (res != nullptr)
                    p.push(*res);
                else throw OperateurException("Erreur ");
            }
            return;
        }
        catch (OperateurException e) {
            p.push(*l2);
            p.push(*l1);
            o.supprimer(Op);
            //e.getInfo();
        }
    }
    if (OperateurToOpUn(Op) != nullptr) {
        if (p.taille() < OperateurToOpUn(Op)->getArite()) {
            o.supprimer(Op);
            throw OperateurException("Erreur : Pas assez d'arguments");
        }
        Litterale* l = &p.top();
        p.pop();
        try {
            OperateurToOpUn(Op)->putLitterale(l);
            Litterale* res = Op->faireOperation();
            C.getCareTaker().clearVecteurLits();
            C.getCareTaker().addLitteraleVecteur(l);
            if(res!=nullptr) p.push(*res);
            return;
        }
        catch (OperateurException e) {
            p.push(*l);
            o.supprimer(Op);
            e.getInfo();
        }
    }
    if (OperateurToOpPile(Op) != nullptr) {
        try {
            Litterale* res = OperateurToOpPile(Op)->faireOperation();
            if (res != nullptr) p.push(*res);
            Controleur::getInstance().getPile().modificationEtat();
            return;
        }
        catch (OperateurException e) {
            o.supprimer(Op);
            e.getInfo();
        }
    }
    throw OperateurException("Erreur : Operateur inconnu");
}

void Controleur::addVar(const QString& s1,LitteraleNumeric* l)
{
    QMap<QString, unsigned int>::const_iterator It = Operateur::listeOperateurs.find(s1);
    if (It != Operateur::listeOperateurs.end())
        throw ComputerException("Erreur : impossible de declarer une variable avec le nom d'un operateur predefini");
    QHash<QString,Programme*>::iterator It1=Progs.find(s1);
    if(It1!=Progs.end())
        Progs.erase(It1);
    QHash<QString,LitteraleNumeric*>::iterator It2 = Var.find(s1);
    if (It2 != Var.end())
        Var.erase(It2);
    Var.insert(s1,l);
    modification();
}

void Controleur::eraseVar(const QString & s)
{
    QHash<QString,LitteraleNumeric*>::iterator It=Var.find(s);
    if(It!=Var.end())
        Var.erase(It);
        modification();
}

void Controleur::addProg(const QString& s1,Programme* l){
    QMap<QString, unsigned int>::const_iterator It = Operateur::listeOperateurs.find(s1);
    if (It != Operateur::listeOperateurs.end())
        throw ComputerException("Erreur : impossible de declarer une variable avec le nom d'un operateur predefini");
    QHash<QString,LitteraleNumeric*>::iterator It1=Var.find(s1);
    if(It1!=Var.end())
        Var.erase(It1);
    QHash<QString,Programme*>::iterator It2=Progs.find(s1);
    if(It2!=Progs.end())
        Progs.erase(It2);
    Progs.insert(s1,l);
    modification();
}

void Controleur::eraseProg(const QString& s){
    QHash<QString,Programme*>::iterator It=Progs.find(s);
    if(It!=Progs.end())
        Progs.erase(It);
        modification();
}

