//
//  computer.cpp
//  Projet
//
//  Created by Rémi Di Vita on 26/04/2016.
//  Copyright © 2016 Rémi Di Vita. All rights reserved.
//

#include "computer.hpp"


Entier* Entier::clone() const{
    return new Entier(*this);
}
Rationel* Rationel::clone() const{
    return new Rationel(*this);
}
OpNumeric* OpNumeric::clone()const{
    return new OpNumeric(*this);
}

OperandeManager::~OperandeManager(){
    for(unsigned int i=0;i<nb;i++) delete opTab[i];
    delete[] opTab;
    nb=0;
    max=0;
}
void OperandeManager::aggrandissementCapacite(){
    Operande** newtab=new Operande*[max+5];// a remplacer par : (max +1)*2
    for(unsigned int i=0;i<nb;i++){
        newtab[i]=opTab[i];
    }
    Operande** old = opTab;
    opTab=newtab;
    max=max+5;
    delete[] old;
}

void OperandeManager::addOperande(Operande& op){
    if(nb==max) aggrandissementCapacite();
    opTab[nb]=op.clone();
    nb++;
}
void OperandeManager::removeOperande(Operande& op){
    unsigned int i=0;
    while(i<nb && opTab[i]!=&op) i++;
    if(i==nb) throw ComputerException("Erreur");
    delete opTab[i];
    i++;
    while(i<nb){
        opTab[i-1]=opTab[i];
        i++;
    }
}

Operande& Item::getOperande()const{
    if(op==nullptr) throw ComputerException("Erreur");
    return *op;
}
//fonction de la Pile
void Pile::aggrandissementCapacite(){
    Item* newtab=new Item[max+5];// a remplacer par : (max +1)*2
    for(unsigned int i=0;i<nb;i++){
        newtab[i]=itTab[i];
    }
    Item* old = itTab;
    itTab=newtab;
    max=max+5;
    delete[] old;

}
void Pile::pop(){
    nb--;
    itTab[nb].raz();
}
Operande& Pile::top()const{
    if(nb==0)throw ComputerException("Erreur");
    return itTab[nb-1].getOperande();
}
void Pile::push(Operande& op){
    if(nb==max) aggrandissementCapacite();
    itTab[nb].setOperande(op);
    nb++;
}
void Controleur::commande(const string& c){
    
}