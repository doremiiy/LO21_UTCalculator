#include "savecontext.h"
#include <QMessageBox>
#include "mainwindow.h"
#include <QTextStream>
using namespace std;

Xml_Dom::Xml_Dom() : QWidget()
{

}
Xml_Dom::~Xml_Dom()
{

}

void Xml_Dom::saveContext(){
    QDomDocument dom("mon_xml");
             QFile doc_xml("xml_doc.xml");
             doc_xml.open(QIODevice::ReadWrite | QIODevice::Truncate);
             QDomElement utcomputer=dom.createElement("utcomputer");
             QDomElement pile=dom.createElement("pile");
             Controleur* controle=&Controleur::getInstance();

                 QDomElement litterale = dom.createElement("litterale");
                 litterale.setAttribute("id","i");
                 litterale.setAttribute("value","L1->afficher()");
                 pile.appendChild(litterale);

             dom.appendChild(utcomputer);
             QString writeur = dom.toString();
             QTextStream stream (&doc_xml);
             stream<<writeur;
             doc_xml.close();
}

void Xml_Dom::retreiveContext(){
    QDomDocument dom("mon_xml");
    QFile xml_doc(":/context.xml");
    if(!xml_doc.open(QIODevice::ReadOnly | QIODevice::Truncate))
    {
        QMessageBox::warning(this, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");
        return;
    }
    if (!dom.setContent(&xml_doc))
    {
     xml_doc.close();
     QMessageBox::warning(this, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être attribué à l'objet QDomDocument.");
     return;
    }
    QDomElement dom_element = dom.documentElement();
    QDomNode pile = dom_element.firstChild();
    QDomNode variables= pile.nextSibling();
    QDomNode programmes= variables.nextSibling();
    QDomNode parametre= programmes.nextSibling();

    //parcour pile
    FabriqueLitterale & f=FabriqueLitterale::getInstance();
    QDomElement temp=pile.lastChildElement();
    while(!temp.isNull()){
        Litterale *res = f.fabriquerLitterale(temp.text());
        controleur.getPile().push(*res);
        temp = temp.previousSiblingElement();
    }
    xml_doc.close();
}

