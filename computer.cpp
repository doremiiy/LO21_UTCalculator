//
//  computer.cpp
//  Projet
//
//  Created by Rémi Di Vita on 26/04/2016.
//  Copyright © 2016 Rémi Di Vita. All rights reserved.
//

#include "computer.hpp"


string Entier::toString() const{
    stringstream s;
    s << value;
    return s.str();
}

Entier* Entier::clone() const {
    return new Entier(*this);
}
string Rationel::toString() const
{
    stringstream s;
    s << numerateur;
    s << denominateur;
    return s.str();
}
Rationel* Rationel::clone() const {
    return new Rationel(*this);
}
string OpNumeric::toString() const{
    stringstream s;
    s << id;
    return s.str();
}
OpNumeric* OpNumeric::clone()const {
    return new OpNumeric(*this);
}

OperandeManager::~OperandeManager() {
    for (unsigned int i = 0; i<nb; i++) delete opTab[i];
    delete[] opTab;
    nb = 0;
    max = 0;
}
void OperandeManager::aggrandissementCapacite() {
    Operande** newtab = new Operande*[max + 5];// a remplacer par : (max +1)*2
    for (unsigned int i = 0; i<nb; i++) {
        newtab[i] = opTab[i];
    }
    Operande** old = opTab;
    opTab = newtab;
    max = max + 5;
    delete[] old;
}

Operande& OperandeManager::addOperande(Operande& op) {
    if (nb == max) aggrandissementCapacite();
    opTab[nb] = op.clone();
    nb++;
    return *opTab[nb-1];
}
void OperandeManager::removeOperande(Operande& op) {
    unsigned int i = 0;
    while (i<nb && opTab[i] != &op) i++;
    if (i == nb) throw ComputerException("Erreur");
    delete opTab[i];
    i++;
    while (i<nb) {
        opTab[i - 1] = opTab[i];
        i++;
    }
}

OperandeManager::Handler OperandeManager::handler = OperandeManager::Handler();

OperandeManager & OperandeManager::getInstance(){
    if (handler.instance == nullptr) handler.instance = new OperandeManager;
    return *handler.instance;
}

void OperandeManager::libererInstance(){
    delete handler.instance;
    handler.instance = nullptr;
}

Operande& Item::getOperande()const {
    if (op == nullptr) throw ComputerException("Erreur");
    return *op;
}
//fonction de la Pile
void Pile::aggrandissementCapacite() {
    Item* newtab = new Item[max + 5];// a remplacer par : (max +1)*2
    for (unsigned int i = 0; i<nb; i++) {
        newtab[i] = itTab[i];
    }
    Item* old = itTab;
    itTab = newtab;
    max = max + 5;
    delete[] old;

}
Pile::~Pile(){
    delete[] itTab;
    nb = 0;
    max = 0;
    message = "";
}
bool Pile::estVide(){
    if (nb == 0) return true;
    return false;
}
void Pile::pop() {
    nb--;
    itTab[nb].raz();
}
Operande& Pile::top()const {
    if (nb == 0)throw ComputerException("Erreur");
    return itTab[nb - 1].getOperande();
}
void Pile::push(Operande& op) {
    if (nb == max) aggrandissementCapacite();
    itTab[nb].setOperande(op);
    nb++;
}
void Pile::afficherPile(ostream & f) const{
    f << "****************************\n";
    f << "M : " << message << "\n";
    f << "------------------------------\n";
    for (unsigned int i = nbAffiche; i > 0; i--) {
        if (i <= nb)
            f << i << ": " << itTab[nb - i].getOperande().toString() << "\n";
        else f << i << ": ";
        cout << "\n";
    }
    f << "---------------------------------\n";
}
void Controleur::commande(const string& c) {
    if (estUneLitterale(c))
        if (estUnEntier(c)) {
            Entier e(stoi(c));
            pi.push(om.addOperande(e));
        }
}


bool estUneLitterale(const string & c){
    if (estUnEntier(c) || estUnRationnel(c)) return true;
    return false;
}

bool estUnEntier(const string & c){
    for (unsigned int i = 0; i < c.length(); i++)
        if (!isdigit(c[i])) return false;
    return true;
}

bool estUnRationnel(const string & c){
    if (c.length() == 1) return false;
    for (unsigned int i = 0; i < c.length(); i++)
        if (c[i] == '/') return true;
    return false;
}
