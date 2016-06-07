/**
\file mainwindow.h
\date 12/06/2016
\author DI VITA Rémi, PFISTER MORGAN
\version 1
\brief  Interface Graphique

Ce fichier defini la fenetre graphique principale\n
**/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include "pile.h"
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

/**
   \class MainWindow
   \brief Decrit la fenetre principale

   \todo Ajouter la vue des programme et la fenetre d'edition
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
    void on_buttonLastarg_clicked();
    void on_buttonDup_clicked();
    void on_buttonDrop_clicked();
    void on_buttonRedo_clicked();
    void on_buttonLastop_clicked();
    void on_buttonUndo_clicked();
    void on_buttonSwap_clicked();
    void on_buttonClear_clicked();
    //Calivier scienifique
    void on_buttonIft_clicked();
    void on_buttonDiv_2_clicked();
    void on_buttonSto_clicked();
    void on_buttonNeg_clicked();
    void on_buttonForget_clicked();
    void on_buttonEval_clicked();
    void on_buttonComp_clicked();
    void on_buttonRe_clicked();
    void on_buttonDen_clicked();
    void on_buttonNum_clicked();
    void on_buttonIm_clicked();
    void on_buttonMod_clicked();
    void on_buttonAnd_clicked();
    void on_buttonEgal_clicked();
    void on_buttonStricSup_clicked();
    void on_buttonOr_clicked();
    void on_buttonNot_clicked();
    void on_buttonSup_clicked();
    void on_buttonStricInf_clicked();
    void on_buttonDif_clicked();
    void on_buttonInf_clicked();
    //buton commande
    void on_buttonC_clicked();
    void on_buttonAC_clicked();
    //Option
    //! \brief Affiche ou Cache le clavier
    void on_activeClavier_clicked();
    void on_activeClavComp_clicked();
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
    //! \brief permet d'editer les programmes
    void on_modifierProg_clicked();
    //! \brief Supprime les programmes sélectionnées
    void on_supprimerProg_clicked();
    //! \brief Supprime toutes les programmes
    void on_toutSupprimerProg_clicked();
    void refreshProgs();
    //Controleur
    //! \brief Rafraichi l'affichage de l'onglet Calcul
    void refreshCalcul();
    //! \brief Rafraichi l'affichage de l'onglet Variable
    void refreshVar();
    //! \brief Envois une commande au controleur
    void getNextCommande();
private:
    Ui::MainWindow *ui;
    Controleur& controleur = Controleur::getInstance();
    QMediaPlayer *player;
};

#endif // MAINWINDOW_H
