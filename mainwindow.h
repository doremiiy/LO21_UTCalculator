/**
\file mainwindow.h
\date 12/06/2016
\author DI VITA Rémi, PFISTER MORGAN
\version 1
\brief  Interface Graphique

Ce fichier defini la fenetre graphique principale\n

\namespace Ui
\brief Interface Graphique

**/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QSound>
#include <QShortcut>
#include <QTableWidget>

#include "progsedit.h"
#include "pile.h"

namespace Ui {
class MainWindow;
}

/**
   \class MainWindow
   \brief Decrit la fenetre principale

   \todo Ajouter la vue des programme et la fenetre d'edition
   \todo Remplacer Ctrl + O par Ctrl + Z et Ctrl+ P pr Crtl + Y

   **/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     //! \brief Contructeur par defaut
    explicit MainWindow(QWidget *parent = 0);
     //! \brief Destructeur
    ~MainWindow();
    //! \brief Fonction pour jouer un son
    void son();
public slots:
    //clavier
    //! \brief Slot correspondant a l'appuis sur le bonton 0
    void on_button0_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton 1
    void on_button1_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton 2
    void on_button2_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton 3
    void on_button3_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton 4
    void on_button4_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton 5
    void on_button5_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton 6
    void on_button6_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton 7
    void on_button7_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton 8
    void on_button8_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton 9
    void on_button9_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton +
    void on_buttonPlus_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton -
    void on_buttonMoins_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton *
    void on_buttonFois_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton /
    void on_buttonDiv_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton .
    void on_buttonPoint_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton Entrer
    void on_buttonEnter_clicked();
    //Operteur pile
    //! \brief Slot correspondant a l'appuis sur le bonton LASTARG
    void on_buttonLastarg_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton DUP
    void on_buttonDup_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton DROP
    void on_buttonDrop_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton REDO
    void on_buttonRedo_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton  LASTOP
    void on_buttonLastop_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton UNDO
    void on_buttonUndo_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton SWAP
    void on_buttonSwap_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton CLEAR
    void on_buttonClear_clicked();
    //Calivier scienifique
    //! \brief Slot correspondant a l'appuis sur le bonton IFT
    void on_buttonIft_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton DIV
    void on_buttonDiv_2_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton STO
    void on_buttonSto_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton NEG
    void on_buttonNeg_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton FORGET
    void on_buttonForget_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton EVAL
    void on_buttonEval_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton $
    void on_buttonComp_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton RE
    void on_buttonRe_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton DEN
    void on_buttonDen_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton NUM
    void on_buttonNum_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton IM
    void on_buttonIm_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton MOD
    void on_buttonMod_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton AND
    void on_buttonAnd_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton =
    void on_buttonEgal_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton >
    void on_buttonStricSup_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton OR
    void on_buttonOr_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton NOT
    void on_buttonNot_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton >=
    void on_buttonSup_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton <
    void on_buttonStricInf_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton !=
    void on_buttonDif_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton =<
    void on_buttonInf_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton [
    void on_buttonLCroch_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton ]
    void on_buttonRCroch_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton Espace
    void on_buttonEsp_clicked();
    //buton commande
    //! \brief Slot correspondant a l'appuis sur le bonton C (Clear One)
    void on_buttonC_clicked();
    //! \brief Slot correspondant a l'appuis sur le bonton AC (All Clear)
    void on_buttonAC_clicked();
    //Option
    //! \brief Affiche ou Cache le clavier Numerique
    void on_activeClavier_clicked();
    //! \brief Affiche ou Cache le clavier Complet
    void on_activeClavComp_clicked();
    //! \brief Affiche ou Cache le clavier des operateurs de la pile
    void on_activeOpPile_clicked();
    //! \brief Change le nombre d'element de la pile a afficher
    void on_taillePile_valueChanged();
    //Variable
    //! \brief Actualise les valeur des varaibles avec les nouvelles modifiées dans la fentre graphique
    void on_modifierVar_clicked();
    //! \brief Supprime les variable sélectionnées
    void on_supprimerVar_clicked();
    //! \brief Supprime toutes les variable
    void on_toutSupprimerVar_clicked();
    //Programme
    //! \brief Supprime les programmes sélectionnées
    void on_suprimerProg_clicked();
    //! \brief Supprime toutes les programmes
    void on_toutSupprimerProg_clicked();
    //! \brief Rafraichi l'affichage de l'onglet Programme
    void refreshProgs();
    void on_vueProgs_itemDoubleClicked(QTableWidgetItem *item);
    //Controleur
    //! \brief Rafraichi l'affichage de l'onglet Calcul
    void refreshCalcul();
    //! \brief Rafraichi l'affichage de l'onglet Variable
    void refreshVar();
    //! \brief Envois une commande au controleur
    void getNextCommande();
    //! \brief Envois La commande undo au controleur grace au racourci Ctrl + O
    void activeUndo();
    //! \brief Envois La commande undo au controleur grace au racourci Ctrl + P
    void activeRedo();
    void on_commande_textChanged();
private:
    Ui::MainWindow *ui;
    Controleur& controleur = Controleur::getInstance();
    QSound *player;
    QShortcut *shortcut1 = new QShortcut(QKeySequence("Ctrl+O"), this);
    QShortcut *shortcut2 = new QShortcut(QKeySequence("Ctrl+P"), this);
    ProgsEdit *fen;
};

#endif // MAINWINDOW_H
