#include "mainwindow.h"
#include "ui_mainwindow.h"

//constructeur de la fenetre
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Pile& P=Pile::getInstance();//creation de la pile
    controleur=new Controleur;
    ui->vuePile->setRowCount(P.getNbToAffiche());
    ui->vuePile->setColumnCount(1);
    ui->message->setStyleSheet("background: cyan; color: black");
    ui->message->setReadOnly(true);
    ui->vuePile->setStyleSheet("background: darker; color: white");
    ui->vuePile->verticalHeader()->setStyleSheet("color: black");
    ui->vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->vuePile->horizontalHeader()->setVisible(false);
    ui->vuePile->horizontalHeader()->setStretchLastSection(true);
    QStringList numberlist;
    for(unsigned int i=P.getNbToAffiche();i>0;i--){
            QString str = QString::number(i);
            str+=" : ";
            numberlist<<str;
            ui->vuePile->setItem(i-1,0,new QTableWidgetItem(""));
        }
    ui->vuePile->setVerticalHeaderLabels(numberlist);
    ui->vuePile->setFixedHeight(P.getNbToAffiche()*ui->vuePile->rowHeight(0)+2);
    connect(&P,SIGNAL(modificationEtat()),this,SLOT(refresh()));
    connect(ui->commande,SIGNAL(returnPressed()),this,SLOT(getNextCommande()));
    ui->commande->setFocus();
}
//destructeur
MainWindow::~MainWindow()
{
    delete ui;
}
//clavier
void MainWindow::on_button0_clicked(){
    ui->commande->insert("0");
}
void MainWindow::on_button1_clicked(){
    ui->commande->insert("1");
}
void MainWindow::on_button2_clicked(){
    ui->commande->insert("2");
}
void MainWindow::on_button3_clicked(){
    ui->commande->insert("3");
}
void MainWindow::on_button4_clicked(){
    ui->commande->insert("4");
}
void MainWindow::on_button5_clicked(){
    ui->commande->insert("5");
}
void MainWindow::on_button6_clicked(){
    ui->commande->insert("6");
}
void MainWindow::on_button7_clicked(){
    ui->commande->insert("7");
}
void MainWindow::on_button8_clicked(){
    ui->commande->insert("8");
}
void MainWindow::on_button9_clicked(){
    ui->commande->insert("9");
}
void MainWindow::on_buttonPlus_clicked(){
    ui->commande->insert("+");
}
void MainWindow::on_buttonMoins_clicked(){
    ui->commande->insert("-");
}
void MainWindow::on_buttonFois_clicked(){
    ui->commande->insert("*");
}
void MainWindow::on_buttonDiv_clicked(){
    ui->commande->insert("/");
}
void MainWindow::on_buttonVirg_clicked(){
    ui->commande->insert(",");
}
void MainWindow::on_buttonEnter_clicked(){
    ui->commande->returnPressed();
}
void MainWindow::refresh(){
    //Le message
    Pile& P=Pile::getInstance();
    ui->message->setText(P.getMessage());
    //Effacer tout
    for(unsigned int i=0;i<P.getNbToAffiche();i++)
        ui->vuePile->item(i,0)->setText("");
    //Mettre a jour
    unsigned int nb=1;
    for(QVector<Item*>::iterator It=P.itTab.begin(); It!=P.itTab.end() && nb<P.getNbToAffiche();++It,++nb)
        ui->vuePile->item(P.getNbToAffiche()-nb,0)->setText((*It)->getLitterale().toString());
}
void MainWindow::getNextCommande(){
    P.setMessage("");
    //Recuperation du texte de la ligne de commande
    QString c = ui->commande->text();
    //Extraction de chaque element de la ligne
    QTextStream stream(&c);
    QString com;
    do{
        try{
            stream>>com;//extraction d'un element
            //envoyer la commande au controleur
            if(com!="") controleur->commande(com);
        }
        catch (LitteraleException e) { P.setMessage(e.getInfo()); }
        catch (OperateurException o) { P.setMessage(o.getInfo()); }
        catch (PileException p) { P.setMessage(p.getInfo()); }
    }while(com!="");
    //Ligne de commande a zero
    ui->commande->clear();
}
