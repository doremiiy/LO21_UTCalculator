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
    Controleur& c=Controleur::getInstance();

    QDomDocument doc;
    QDomElement context = doc.createElement("context");
    doc.appendChild(context);

    //Noeud pile
    if(c.getPile().getState().size()>0){
        QDomElement pile = doc.createElement("pile");
        context.appendChild(pile);
        for(int i=0;i<c.getPile().getState().size();i++){
            QDomElement litterale = doc.createElement("litterale");
            pile.appendChild(litterale);
            QString s=c.getPile().itTab[i]->getLitterale().toString();
            QDomText valeurLit = doc.createTextNode(s);
            litterale.appendChild(valeurLit);
        }
    }

    //Noeud variables
    QHash<QString,LitteraleNumeric*>::iterator It1=c.Var.begin();
    if(It1!=c.Var.end()){
        QDomElement variables = doc.createElement("variables");
        context.appendChild(variables);
        for(It1=c.Var.begin();It1!=c.Var.end();++It1){
            QDomElement var = doc.createElement("var");
            variables.appendChild(var);
            QString s1=It1.key();
            QString s2=It1.value()->toString();
            QDomText valeurVar = doc.createTextNode(s1+"_"+s2);
            var.appendChild(valeurVar);
        }
    }

    //Noeud Programmes
    QHash<QString,Programme*>::iterator It2=c.Progs.begin();
    if(It2!=c.Progs.end()){
        QDomElement programmes = doc.createElement("programmes");
        context.appendChild(programmes);
        for(It2=c.Progs.begin();It2!=c.Progs.end();++It2){
            QDomElement prog = doc.createElement("prog");
            programmes.appendChild(prog);
            QString s1=It2.key();
            QString s2=It2.value()->toString();
            QDomText valeurProg = doc.createTextNode(s1+"_"+s2);
            prog.appendChild(valeurProg);
        }
    }

    QDomProcessingInstruction instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"ISO-8859-1\"");
    doc.insertBefore(instruction,context);
    //Creation du fichier
    QFile fichier("fichier.xml");
    //ouverture du fichier
    if(!fichier.open(QFile::ReadWrite | QFile::Truncate))
    {
    return;
    }
    QTextStream out(&fichier);
    //Sauvegarde
    doc.save(out,4,QDomDocument::EncodingFromDocument);
    //fermeture du fichier
    fichier.close();
}

void Xml_Dom::retreiveContext(){
    QDomDocument dom("mon_xml");
    QFile xml_doc("fichier.xml");
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
    FabriqueOperateur& o=FabriqueOperateur::getInstance();
    QDomElement temp=pile.lastChildElement();
    while(!temp.isNull()){
        Litterale *res = f.fabriquerLitterale(temp.text());
        controleur.getPile().push(*res);
        temp = temp.previousSiblingElement();
    }

    //parcours variables
    QDomElement var=variables.lastChildElement();
    while(!var.isNull()){
        QString s=var.text();
        QString at="",val="";
        int i=0;
        while(s[i]!='_'){
            at+=s[i];
            i++;
        }
        i++;
        at='\''+at+'\'';
        while(s[i]!='\0'){
            val+=s[i];
            i++;
        }
        OperateurBinaire* Op=OperateurToOpBin(o.fabriquer("STO"));
        Op->putLitterale(f.fabriquerLitterale(val),f.fabriquerExpression(at));
        Litterale* res=Op->faireOperation();
        var = var.previousSiblingElement();
        delete res;
    }

    //parcours programmes
    QDomElement prog=programmes.lastChildElement();
    while(!prog.isNull()){
        QString s=prog.text();
        QString at="",val="";
        int i=0;
        while(s[i]!='_'){
            at+=s[i];
            i++;
        }
        i++;
        at='\''+at+'\'';
        while(s[i]!='\0'){
            val+=s[i];
            i++;
        }
        OperateurBinaire* Op=OperateurToOpBin(o.fabriquer("STO"));
        Op->putLitterale(f.fabriquerLitterale(val),f.fabriquerExpression(at));
        Litterale* res=Op->faireOperation();
        prog = prog.previousSiblingElement();
        delete res;
    }
    xml_doc.close();
}

