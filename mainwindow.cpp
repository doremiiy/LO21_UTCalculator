
#include "mainwindow.h"
#include "ui_mainwindow.h"

//constructeur de la fenetre
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //restauration du contexte
    test->retreiveContext();
    //Creation vuePile
    Pile& P = controleur.getPile();
    ui->vuePile->setRowCount(P.getNbToAffiche());
    ui->vuePile->setColumnCount(1);
    ui->vuePile->setStyleSheet("background: darker; color: white");
    ui->vuePile->verticalHeader()->setStyleSheet("color: black");
    ui->vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->vuePile->horizontalHeader()->setVisible(false);
    ui->vuePile->horizontalHeader()->setStretchLastSection(true);
    //Creation la vue des variable
        //VueVArID
    ui->vueVarId->setColumnCount(1);
    ui->vueVarId->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->vueVarId->horizontalHeader()->setVisible(false);
    ui->vueVarId->verticalHeader()->setVisible(false);
    ui->vueVarId->horizontalHeader()->setStretchLastSection(true);
        //vueVarValue
    ui->vueVarValue->setColumnCount(1);
    ui->vueVarValue->horizontalHeader()->setVisible(false);
    ui->vueVarValue->verticalHeader()->setVisible(false);
    ui->vueVarValue->horizontalHeader()->setStretchLastSection(true);
    //Creation vueProgs
    ui->vueProgs->setColumnCount(1);
    ui->vueProgs->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->vueProgs->horizontalHeader()->setVisible(false);
    ui->vueProgs->verticalHeader()->setVisible(false);
    ui->vueProgs->horizontalHeader()->setStretchLastSection(true);
    //Creation du son
    player = new QSound(":/beep.wav",this);
    //Paramtre de Message
    ui->message->setStyleSheet("background: cyan; color: black");
    ui->message->setReadOnly(true);
    //conection des signaux
    connect(&P,SIGNAL(modificationEtat()),this,SLOT(refreshCalcul()));
    connect(&controleur,SIGNAL(modification()),this,SLOT(refreshVar()));
    connect(&controleur,SIGNAL(modification()),this,SLOT(refreshProgs()));
    connect(ui->commande,SIGNAL(returnPressed()),this,SLOT(getNextCommande()));
    connect(shortcut1, SIGNAL(activated()), this, SLOT(activeUndo()));
    connect(shortcut2, SIGNAL(activated()), this, SLOT(activeRedo()));
    //initialisation
    refreshVar();
    refreshProgs();
    ui->commande->setFocus();
    on_activeClavier_clicked();//on clache le clavier numerique
    on_activeClavComp_clicked();//on cache le clavier complet
    on_activeOpPile_clicked();//on cache le clavier operateur
    on_taillePile_valueChanged();
    ui->message->setText("Bonjour");
    fen=new ProgsEdit(this);
}
//destructeur
MainWindow::~MainWindow()
{
    test->saveContext();
    delete ui;
}
//CTRL + O : Undo
void MainWindow::activeUndo(){
    controleur.commande("UNDO");
}
void MainWindow::activeRedo(){
    controleur.commande("REDO");
}
//clavier
void MainWindow::on_button0_clicked(){
    ui->commande->insert("0");
    //test->saveContext();
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
    ui->commande->insert(" +");
}
void MainWindow::on_buttonMoins_clicked(){
    ui->commande->insert(" -");
}
void MainWindow::on_buttonFois_clicked(){
    ui->commande->insert(" *");
}
void MainWindow::on_buttonDiv_clicked(){
    ui->commande->insert(" /");
}
void MainWindow::on_buttonPoint_clicked(){
    ui->commande->insert(".");
}
void MainWindow::on_buttonEnter_clicked(){
    ui->commande->returnPressed();
}
void MainWindow::on_buttonLastarg_clicked(){
    ui->commande->insert(" LASTARGS");
}
void MainWindow::on_buttonDup_clicked(){
    ui->commande->insert(" DUP");
}
void MainWindow::on_buttonDrop_clicked(){
    ui->commande->insert(" DROP");
}
void MainWindow::on_buttonRedo_clicked(){
    ui->commande->insert(" REDO");
}
void MainWindow::on_buttonLastop_clicked(){
    ui->commande->insert(" LASTOP");
}
void MainWindow::on_buttonUndo_clicked(){
    ui->commande->insert(" UNDO");
}
void MainWindow::on_buttonSwap_clicked(){
    ui->commande->insert(" SWAP");
}
void MainWindow::on_buttonClear_clicked(){
    ui->commande->insert(" CLEAR");
}
void MainWindow::on_buttonIft_clicked(){
    ui->commande->insert(" IFT");
}
void MainWindow::on_buttonDiv_2_clicked(){
    ui->commande->insert(" DIV");
}
void MainWindow::on_buttonSto_clicked(){
    ui->commande->insert(" STO");
}
void MainWindow::on_buttonNeg_clicked(){
    ui->commande->insert(" NEG");
}
void MainWindow::on_buttonForget_clicked(){
    ui->commande->insert(" FORGET");
}
void MainWindow::on_buttonEval_clicked(){
    ui->commande->insert(" EVAL");
}
void MainWindow::on_buttonComp_clicked(){
    ui->commande->insert(" $");
}
void MainWindow::on_buttonRe_clicked(){
    ui->commande->insert(" RE");
}
void MainWindow::on_buttonDen_clicked(){
    ui->commande->insert(" DEN");
}
void MainWindow::on_buttonNum_clicked(){
    ui->commande->insert(" NUM");
}
void MainWindow::on_buttonIm_clicked(){
    ui->commande->insert(" IM");
}
void MainWindow::on_buttonMod_clicked(){
    ui->commande->insert(" MOD");
}
void MainWindow::on_buttonAnd_clicked(){
    ui->commande->insert(" AND");
}
void MainWindow::on_buttonEgal_clicked(){
    ui->commande->insert(" =");
}
void MainWindow::on_buttonStricSup_clicked(){
    ui->commande->insert(" >");
}
void MainWindow::on_buttonOr_clicked(){
    ui->commande->insert(" OR");
}
void MainWindow::on_buttonNot_clicked(){
    ui->commande->insert(" NOT");
}
void MainWindow::on_buttonSup_clicked(){
    ui->commande->insert(" >=");
}
void MainWindow::on_buttonStricInf_clicked(){
    ui->commande->insert(" <");
}
void MainWindow::on_buttonDif_clicked(){
    ui->commande->insert(" !=");
}
void MainWindow::on_buttonInf_clicked(){
    ui->commande->insert(" <=");
}
void MainWindow::on_buttonC_clicked(){
    ui->commande->backspace();
}
void MainWindow::on_buttonAC_clicked(){
    ui->commande->clear();
}
void MainWindow::on_buttonLCroch_clicked(){
    ui->commande->insert("[");
}
void MainWindow::on_buttonRCroch_clicked(){
    ui->commande->insert("]");
}
void MainWindow::on_buttonEsp_clicked(){
    ui->commande->insert(" ");
}
void MainWindow::on_activeClavier_clicked(){
    if(ui->activeClavier->isChecked()){
        ui->button0->show();
        ui->button1->show();
        ui->button2->show();
        ui->button3->show();
        ui->button4->show();
        ui->button5->show();
        ui->button6->show();
        ui->button7->show();
        ui->button8->show();
        ui->button9->show();
        ui->buttonPlus->show();
        ui->buttonMoins->show();
        ui->buttonFois->show();
        ui->buttonDiv->show();
        ui->buttonPoint->show();
        ui->buttonEnter->show();
    }
    else{
        ui->button0->hide();
        ui->button1->hide();
        ui->button2->hide();
        ui->button3->hide();
        ui->button4->hide();
        ui->button5->hide();
        ui->button6->hide();
        ui->button7->hide();
        ui->button8->hide();
        ui->button9->hide();
        ui->buttonPlus->hide();
        ui->buttonMoins->hide();
        ui->buttonFois->hide();
        ui->buttonDiv->hide();
        ui->buttonPoint->hide();
        ui->buttonEnter->hide();
    }
}
void MainWindow::on_activeClavComp_clicked(){
    if(ui->activeClavComp->isChecked()){
        ui->buttonIft->show();
        ui->buttonDiv_2->show();
        ui->buttonSto->show();
        ui->buttonNeg->show();
        ui->buttonForget->show();
        ui->buttonEval->show();
        ui->buttonComp->show();
        ui->buttonRe->show();
        ui->buttonDen->show();
        ui->buttonNum->show();
        ui->buttonIm->show();
        ui->buttonMod->show();
        ui->buttonAnd->show();
        ui->buttonEgal->show();
        ui->buttonStricSup->show();
        ui->buttonOr->show();
        ui->buttonNot->show();
        ui->buttonSup->show();
        ui->buttonStricInf->show();
        ui->buttonDif->show();
        ui->buttonInf->show();
        ui->buttonLCroch->show();
        ui->buttonRCroch->show();
        ui->buttonEsp->show();
    }
    else{
        ui->buttonIft->hide();
        ui->buttonDiv_2->hide();
        ui->buttonSto->hide();
        ui->buttonNeg->hide();
        ui->buttonForget->hide();
        ui->buttonEval->hide();
        ui->buttonComp->hide();
        ui->buttonRe->hide();
        ui->buttonDen->hide();
        ui->buttonNum->hide();
        ui->buttonIm->hide();
        ui->buttonMod->hide();
        ui->buttonAnd->hide();
        ui->buttonEgal->hide();
        ui->buttonStricSup->hide();
        ui->buttonOr->hide();
        ui->buttonNot->hide();
        ui->buttonSup->hide();
        ui->buttonStricInf->hide();
        ui->buttonDif->hide();
        ui->buttonInf->hide();
        ui->buttonLCroch->hide();
        ui->buttonRCroch->hide();
        ui->buttonEsp->hide();
    }
}
void MainWindow::on_activeOpPile_clicked(){
    if(ui->activeOpPile->isChecked()){
        ui->buttonLastarg->show();
        ui->buttonDup->show();
        ui->buttonDrop->show();
        ui->buttonRedo->show();
        ui->buttonLastop->show();
        ui->buttonUndo->show();
        ui->buttonSwap->show();
        ui->buttonClear->show();
    }
    else{
        ui->buttonLastarg->hide();
        ui->buttonDup->hide();
        ui->buttonDrop->hide();
        ui->buttonRedo->hide();
        ui->buttonLastop->hide();
        ui->buttonUndo->hide();
        ui->buttonSwap->hide();
        ui->buttonClear->hide();
    }
}

void MainWindow::on_taillePile_valueChanged(){
    Pile& P = Controleur::getInstance().getPile();
    P.setNbToAffiche((unsigned)ui->afficheTaillePile->text().toInt());
    ui->vuePile->clear();
    ui->vuePile->setRowCount(P.getNbToAffiche());
    QStringList numberlist;
    for(unsigned int i=P.getNbToAffiche();i>0;i--){
            QString str = QString::number(i);
            str+=" : ";
            numberlist<<str;
            ui->vuePile->setItem(i-1,0,new QTableWidgetItem(""));
        }
    ui->vuePile->setVerticalHeaderLabels(numberlist);
    ui->vuePile->setFixedHeight(P.getNbToAffiche()*ui->vuePile->rowHeight(0)+2);
    refreshCalcul();
}
//Variable
void MainWindow::on_modifierVar_clicked(){//pas fonctionelle
    FabriqueLitterale &f=FabriqueLitterale::getInstance();
    ui->message->setText("value changed");
    QHash<QString,LitteraleNumeric*>::iterator It = controleur.Var.begin();
    unsigned int nb=0;
    while(It!=controleur.Var.end()){
        QString id=ui->vueVarId->item(nb,0)->text();
        QString value=ui->vueVarValue->item(nb,0)->text();
        QHash<QString,LitteraleNumeric*>::iterator It2 = controleur.Var.find(id);
        if(value!=It2.value()->toString()){
            LitteraleNumeric *temp =f.fabriquerLitNum(value);
            controleur.Var.erase(It2);
            controleur.Var.insert(id,temp);
        }
        nb++;
        It++;
    }
    refreshVar();
}
void MainWindow::on_supprimerVar_clicked(){
    QList<QTableWidgetItem *> items=ui->vueVarId->selectedItems();
    for(QList<QTableWidgetItem *>::iterator It=items.begin(); It!=items.end();++It)
        controleur.eraseVar((*It)->text());
    refreshVar();       
}
void MainWindow::on_toutSupprimerVar_clicked(){
    controleur.Var.clear();
    refreshVar();
}
void MainWindow::refreshVar(){//Mettre a jour de la vueVar
    //Set message
    ui->message->setText("Enregistré");
    //Effacer tout
    ui->vueVarId->clear();
    ui->vueVarValue->clear();
    //Mettre a jour de la vueVar
    ui->vueVarId->setRowCount(controleur.Var.count());
    ui->vueVarValue->setRowCount(controleur.Var.count());
    unsigned int nb=0;
    for(QHash<QString,LitteraleNumeric*>::iterator It=controleur.Var.begin(); It!=controleur.Var.end();++It,nb++){
        ui->vueVarId->setItem(nb,0,new QTableWidgetItem(It.key()));
        ui->vueVarValue->setItem(nb,0,new QTableWidgetItem(It.value()->toString()));
    }
    ui->vueVarId->setFixedHeight(5*ui->vueVarId->rowHeight(0)+2);
    ui->vueVarValue->setFixedHeight(5*ui->vueVarValue->rowHeight(0)+2);
}
//Programme
void MainWindow::on_suprimerProg_clicked(){
    QList<QTableWidgetItem *> items=ui->vueProgs->selectedItems();
    for(QList<QTableWidgetItem *>::iterator It=items.begin(); It!=items.end();++It)
        controleur.eraseProg((*It)->text());
    refreshProgs();
}

void MainWindow::on_toutSupprimerProg_clicked(){
    controleur.Progs.clear();
    refreshProgs();
}
void MainWindow::refreshProgs(){
    //Set message
    ui->message->setText("Enregistré");
    //Effacer tout
    ui->vueProgs->clear();
    //Mettre a jour de la vueVar
    ui->vueProgs->setRowCount(controleur.Progs.count());
    unsigned int nb=0;
    for(QHash<QString,Programme*>::iterator It=controleur.Progs.begin(); It!=controleur.Progs.end();++It,nb++){
        ui->vueProgs->setItem(nb,0,new QTableWidgetItem(It.key()));
    }
    ui->vueProgs->setFixedHeight(5*ui->vueProgs->rowHeight(0)+2);
}
//ProgEdit
void MainWindow::on_vueProgs_itemDoubleClicked(QTableWidgetItem * item){
    QHash<QString,Programme*>::iterator It=controleur.Progs.find(item->text());
    fen->setText(It.value()->toString());
    fen->setlabel(It.key());
    fen->show();
}
//SON
void MainWindow::son(){
    if(ui->activeSon->isChecked()) player->play();
}

void MainWindow::refreshCalcul(){//Mettre a jour de la vuePile
    //Le message
    ui->message->clear();
    //Effacer tout
    Pile& P = controleur.getInstance().getPile();
    for(unsigned int i=0;i<P.getNbToAffiche();i++)
        ui->vuePile->item(i,0)->setText("");
    //Mettre a jour de la vuePile
    unsigned int nb=1;
    for(QVector<Item*>::iterator It=P.itTab.begin(); It!=P.itTab.end() && nb<=P.getNbToAffiche();++It,++nb)
        ui->vuePile->item(P.getNbToAffiche()-nb,0)->setText((*It)->getLitterale().toString());
}
void MainWindow::on_commande_textChanged(){
    if(endIsOperateur(ui->commande->text())) getNextCommande();
}

void MainWindow::getNextCommande(){
    QString c = ui->commande->text();
    try{
        controleur.commande(c);
        ui->commande->clear();
    }
    catch (ComputerException e) { ui->message->setText(e.getInfo());son(); }
}
