#ifndef SAVECONTEXT_H
#define SAVECONTEXT_H

#include <QtXml>
#include <QWidget>
#include "pile.h"

/**
   \class Xml_Dom
   \brief Sauvegarde du contexte
**/
class Xml_Dom : public QWidget
{
private:
     Controleur &controleur = Controleur::getInstance();
public:
    Xml_Dom();
    ~Xml_Dom();
    void retreiveContext();
//public slots:
    void saveContext();
};

#endif // SAVECONTEXT_H
