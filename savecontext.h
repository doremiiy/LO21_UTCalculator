#ifndef SAVECONTEXT_H
#define SAVECONTEXT_H

#include <QtXml>
#include <QWidget>
//#include "mainwindow.h"
#include "pile.h"

class Xml_Dom : public QWidget
{
private:
     QDomDocument *dom;
     Controleur &controleur = Controleur::getInstance();
public:
    Xml_Dom();
    ~Xml_Dom();
    void retreiveContext();
//public slots:
    void saveContext();
};

#endif // SAVECONTEXT_H
