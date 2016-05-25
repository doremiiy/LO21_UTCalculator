
#include "qcomputer.h"
#include <algorithm>

QComputer::QComputer(QWidget *parent):QWidget(parent){
    //Creation des Objets
    //Pile& P=Pile::getInstance();
    P.setMessage("Bienvenue");
    controleur = new Controleur;
    message = new QLineEdit(this);
    vuePile = new QTableWidget(P.getNbToAffiche(),1,this);
    commande = new QLineEdit(this);
    couche = new QVBoxLayout(this);
    //<positionnement des Objets
    couche->addWidget(message);
    couche->addWidget(vuePile);
    couche->addWidget(commande);
    setLayout(couche);
    //Titre
    this->setWindowTitle("UTComputer");
    //couleur
    message->setStyleSheet("background: cyan; color: black");
    message->setReadOnly(true);
    vuePile->setStyleSheet("background: darker; color: white");
    vuePile->verticalHeader()->setStyleSheet("color: black");
    //Donner la bonne apparence a vuePile
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vuePile->horizontalHeader()->setVisible(false);
    vuePile->horizontalHeader()->setStretchLastSection(true);
    //crée une liste de label
    QStringList numberlist;
    for(unsigned int i=P.getNbToAffiche();i>0;i--){
        QString str = QString::number(i);
        str+=" : ";
        numberlist<<str;
        vuePile->setItem(i-1,0,new QTableWidgetItem(""));
    }
    //
    vuePile->setVerticalHeaderLabels(numberlist);
    vuePile->setFixedHeight(P.getNbToAffiche()*vuePile->rowHeight(0)+2);
    //Connection des signaux slot
    connect(&P,SIGNAL(modificationEtat()),this,SLOT(refresh()));
    connect(commande,SIGNAL(returnPressed()),this,SLOT(getNextCommande()));
    //Focus a la barre de commande
    commande->setFocus();
}

void QComputer::refresh(){
    //Le message
    Pile& P=Pile::getInstance();
    message->setText(P.getMessage());
    //Effacer tout
    for(unsigned int i=0;i<P.getNbToAffiche();i++)
        vuePile->item(i,0)->setText("");
    //Mettre a jour
    unsigned int nb=1;
    //for(QVector<Item*>::const_iterator It=P.itTab.cbegin(); It!=P.itTab.cend() && nb<P.getNbToAffiche();++It,++nb)
    //    vuePile->item(P.getNbToAffiche()-nb,0)->setText((*It)->getLitterale().toString()/*"Bonjour"*/);
    QVector<Item*>::const_iterator It = P.itTab.begin();
    for (unsigned int i = 5; i > 0; i--){
        if (6-i <= P.taille()) {
            vuePile->item(i-1,0)->setText((*It)->getLitterale().toString()/*"Bonjour"*/);
            ++It;
        }
    }
}

void QComputer::getNextCommande(){
    P.setMessage("");
    //Recuperation du texte de la ligne de commande
    QString c = commande->text();
    //Extraction de chaque element de la ligne
    QTextStream stream(&c);
    QString com;
    do{
        try{
            stream>>com;//extraction d'un element
            //envoyer la commande au controleur
            if(com!="") controleur->commande(com);
        }
        catch (LitteraleException e) { P.setMessage(e.getInfo()); system("cls"); }
        catch (OperateurException o) { P.setMessage(o.getInfo()); system("cls"); }
        catch (PileException p) { P.setMessage(p.getInfo()); system("cls"); }
    }while(com!="");
    //Ligne de commande a zero
    commande->clear();
}
