#ifndef Pile_h
#define Pile_h

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <sstream>
#include <regex>
#include <list>
#include <QVector>
#include <QString>
#include <QTextStream>


#include "litterale.h"
#include "operateur.h"

using namespace std;

class Operateur;
class PileException;
class Item;
class Pile;

class PileException {
private:
    QString info;
public:
    QString getInfo() const { return info; }
    PileException(const QString& s) :info(s) {}
};

class Item {
private:
    Litterale& L;
public:
    Item(Litterale& l) :L(*l.Clone()) {}
    void setLitterale(Litterale& l) { L = *l.Clone(); }
    Litterale& getLitterale() const { return L; }
};

/*class Memento {
private:
    QVector<Item*> state;
public:
    Memento(const QVector<Item*> items);
    QVector<Item*> getState() const { return state; }
};*/

class Pile:public QObject {
private:
    Q_OBJECT
    friend class MainWindow;
    QVector<Item*> itTab;
    unsigned int nbAffiche;
    QString message;
    Pile() :nbAffiche(5), message("") { QVector<Item*> itTab = *(new QVector<Item*>); }
    ~Pile();
    void operator=(const Pile& p);
    Pile(const Pile& p);
    struct Handler {
        Pile* instance;
        Handler() :instance(nullptr) {}
        ~Handler() { delete instance; }
    };
    static Handler handler;
public:
    //QVector<Item*> getPile() const { return itTab; }
    static Pile& getInstance();
    static void libererInstance();
    bool estVide() const { return itTab.empty(); }
    void pop();
    Litterale& top() const;
    void push(Litterale& L);
    unsigned int taille() const { return itTab.size(); }
    void setNbToAffiche(unsigned int n) { nbAffiche = n; }
    unsigned int getNbToAffiche() const { return nbAffiche; }
    void afficherPile(QTextStream& f) const;
    void setMessage(const QString& s) { message = s; modificationEtat(); }
    QString getMessage() const { return message; }
    //void setState(QVector<Item*> items);
    //QVector<Item*> getState() { return itTab; }
    //Memento saveStateToMemento() { return new Memento(itTab); }
    //void getStateFromMemento() { itTab = Memento.getState(); }
signals://Signaux pour Qt
    void modificationEtat();

};

/*class CareTaker {
private:
    list<Memento> mementoList;
    //Operateur* DernierOpApplique;
public:
    //CareTaker():DernierOpApplique(nullptr){}
    //Operateur* getDernierOpApplique() const { return DernierOpApplique; }
    //void setDernierOpApplique(Operateur* Op) { delete DernierOpApplique; DernierOpApplique = Op->Clone(); }
    //QVector<const Litterale*> getListLitterales() const { return ListLitterales; }
    //void clearListLitterales() { ListLitterales.clear(); }
    void Add(Memento state) { mementoList.push_back(state); }
    Memento get() {return mementoList.}
    QVector<Item*> undo();
    QVector<Item*> redo();
};*/

class Controleur {
private:
    Pile& p;
    //CareTaker& ct;
public:
    Controleur() :p(Pile::getInstance()) {}
    //void saveOp(Operateur* Op);
    void commande(const QString& s);
    void appliquerOperateur(Operateur* Op);
};


#endif
