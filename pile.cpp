
#include "Pile.h"

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
        throw PileException("Erreur : pile vide");
}

Litterale & Pile::top() const
{
    if (!estVide())
        return itTab.front()->getLitterale();
    throw PileException("Erreur : pile vide");
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
        throw PileException("Erreur impossible d'appliquer l'operateur");
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

void Controleur::commande(const QString & s)
{
    FabriqueLitterale& f = FabriqueLitterale::getInstance();
    FabriqueOperateur& o = FabriqueOperateur::getInstance();
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
                if(It==Var.end()){
                    QString stmp="'"+s+"'";
                    Litterale* l=f.fabriquerExpression(stmp);
                    p.push(*l);
                    f.supprimer(l);
                }
                if(It!=Var.end()){
                    p.push(*It.value());
                }
            }
            else {
                Litterale* l = f.fabriquerLitterale(s);
                p.push(*l);
                f.supprimer(l);
            }
        }
    }
}

void Controleur::appliquerOperateur(Operateur * Op)
{
    FabriqueLitterale& f = FabriqueLitterale::getInstance();
    FabriqueOperateur& o = FabriqueOperateur::getInstance();
    Controleur& C = Controleur::getInstance();
    if (OperateurToOpBin(Op) != nullptr) {
        if (p.taille() < OperateurToOpBin(Op)->getArite()) {
            o.supprimer(Op);
            throw OperateurException("Erreur : Pas assez d'arguments");
        }
        Litterale* l1 = &p.top();
        p.pop();
        Litterale* l2 = &p.top();
        p.pop();
        try {
            OperateurToOpBin(Op)->putLitterale(l2, l1);
            Litterale* res = Op->faireOperation();
            C.getCareTaker().clearVecteurLits();
            C.getCareTaker().addLitteraleVecteur(l1);
            C.getCareTaker().addLitteraleVecteur(l2);
            if (res != nullptr)
                p.push(*res);
            else throw PileException("Erreur ");
            return;
        }
        catch (OperateurException e) {
            p.push(*l2);
            p.push(*l1);
            o.supprimer(Op);
            e.getInfo();
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
    map<QString, unsigned int>::const_iterator It = Operateur::listeOperateurs.find(s1);
    if (It != Operateur::listeOperateurs.end())
        throw PileException("Erreur : impossible de declarer une variable avec le nom d'un operateur predefini");
    QHash<QString,LitteraleNumeric*>::iterator It2 = Var.find(s1);
    if (It2 != Var.end())
        Var.erase(It2);
    Var.insert(s1,l);
}

/*void Controleur::eraseVar(const string & s)
{
    QMap<string, string>::const_iterator It=Var.find(s);
    if(It!=Var.end())
        Var.erase(It);
}

LitteraleNumeric * Controleur::getVar(const string & s)
{
    FabriqueLitterale& f = FabriqueLitterale::getInstance();
    map<string, string>::const_iterator It = Var.find(s);
    if (It == Var.end())
        throw PileException("Erreur : variable inconnue");
    else
        return f.fabriquerLitNum((*It).second);
}*/

