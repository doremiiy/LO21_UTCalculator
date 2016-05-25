#ifndef QCOMPUTER_H
#define QCOMPUTER_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QObject>
#include <QDebug>
#include "pile.h"

class QComputer : public QWidget{
    Q_OBJECT

    QLineEdit* message;
    QTableWidget* vuePile;
    QLineEdit* commande;
    QVBoxLayout* couche;
    Pile& P=Pile::getInstance();
    Controleur* controleur;
public:
    explicit QComputer(QWidget *parent = 0);
public slots:
    void refresh();
    void getNextCommande();
};

#endif // QCOMPUTER_H

