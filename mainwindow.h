#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include "pile.h"
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    //clavier
    void on_button0_clicked();
    void on_button1_clicked();
    void on_button2_clicked();
    void on_button3_clicked();
    void on_button4_clicked();
    void on_button5_clicked();
    void on_button6_clicked();
    void on_button7_clicked();
    void on_button8_clicked();
    void on_button9_clicked();
    void on_buttonPlus_clicked();
    void on_buttonMoins_clicked();
    void on_buttonFois_clicked();
    void on_buttonDiv_clicked();
    void on_buttonPoint_clicked();
    void on_buttonEnter_clicked();
    //Option
    void on_activeClavier_clicked();
    void on_taillePile_valueChanged();
    //Variable
    void on_modifierVar_clicked();
    void on_supprimerVar_clicked();
    void on_toutSupprimerVar_clicked();
    //Controleur
    void refreshCalcul();
    void refreshVar();
    void getNextCommande();
private:
    Ui::MainWindow *ui;
    Controleur& controleur = Controleur::getInstance();
    QMediaPlayer *player;
public:
    void son();
};

#endif // MAINWINDOW_H
