#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QSound>
#include "pile.h"

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
    void on_activeClavier_clicked();
    void on_taillePile_valueChanged();
    void refresh();
    void getNextCommande();
private:
    Ui::MainWindow *ui;
    //Pile& P;
    Controleur* controleur;
};

#endif // MAINWINDOW_H
