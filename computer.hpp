//
//  computer.hpp
//  Projet
//
//  Created by Rémi Di Vita on 26/04/2016.
//  Copyright © 2016 Rémi Di Vita. All rights reserved.
//

#ifndef computer_hpp
#define computer_hpp

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class ComputerException {
private:
    string info;
public:
    ComputerException(const string& str) :info(str) {}
    string getInfo() const { return info; }
};

class Operande {
    friend class OperandeManager;
public:
    virtual Operande* clone()const = 0;
    virtual string toString() const = 0;
    //virtual ~Operande(); ?????

};

class OperandeManager {
private:
    Operande** opTab;
    unsigned int nb;
    unsigned int max;
    OperandeManager():opTab(nullptr), nb(0), max(0) {}
    void aggrandissementCapacite();
    ~OperandeManager();
    OperandeManager(const OperandeManager& m);
    OperandeManager& operator=(const OperandeManager& m);
    struct Handler {
        OperandeManager* instance;
        Handler() :instance(nullptr){}
        ~Handler() { delete instance; }
    };
    static Handler handler;
public:
    Operande& addOperande(Operande& op);
    void removeOperande(Operande& op);
    static OperandeManager& getInstance();
    static void libererInstance();
    //Ajouter iterator

};

class Literale : public Operande {
    virtual Literale* clone()const = 0;
};
class LiteraleNumeric :public Literale {
    virtual LiteraleNumeric* clone() const = 0;//a verifier pour le virtual
};

class Entier :public LiteraleNumeric {
private:
    int value;
public:
    string toString() const;
    Entier(const int& n) :value(n) {}
    Entier* clone() const;
    const int getValue() { return value; }
};
class Rationel :public LiteraleNumeric {
private:
    int numerateur;
    int denominateur;
public:
    string toString() const;
    Rationel(const int& n, const int& d) :numerateur(n), denominateur(d) {}
    Rationel* clone()const;
    const int getNumerateur()const { return numerateur; }
    const int getDenominateur()const { return denominateur; }
};

class Operateur : public Operande {
    virtual Operateur* clone()const = 0;
};
class OpNumeric :public Operateur {
private:
    string id;
    int arite;
public:
    string toString() const;
    OpNumeric(const string& s, const int& n) :id(s), arite(n) {}
    OpNumeric* clone()const;
    const string getId() const { return id; }
    const int getArite() const { return arite; }
};

class Item {
private:
    Operande* op;
public:
    Item() :op(nullptr) {}
    void raz() { op = nullptr; }
    void setOperande(Operande& e) { op = &e; }
    Operande& getOperande()const;
};

class Pile {
private:
    Item * itTab;
    unsigned int nb;
    unsigned int max;
    string message;
    void aggrandissementCapacite();
    unsigned int nbAffiche;
public:
    Pile():itTab(nullptr),nb(0),max(0),message(""),nbAffiche(4){}
    ~Pile();
    bool estVide();
    void setMessage(const string& s) { message = s; }
    void pop();
    Operande& top() const;
    void push(Operande& op);
    unsigned int taille()const { return nb; }
    void setNbToAffiche(unsigned int n) { nbAffiche = n; }
    unsigned int getNbToAffiche() const{ return nbAffiche; }
    void afficherPile(ostream& f) const;
};
class Controleur {
private:
    OperandeManager& om;
    Pile& pi;
public:
    Controleur(OperandeManager& e, Pile& p) :om(e), pi(p) {}
    void commande(const string& c);
};

bool estUneLitterale(const string& c);
bool estUnEntier(const string& c);
bool estUnRationnel(const string& c);

#endif /* computer_hpp */

