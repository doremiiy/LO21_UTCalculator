#include "progsedit.h"
#include "ui_progsedit.h"
#include "mainwindow.h"
ProgsEdit::ProgsEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgsEdit)
{
    ui->setupUi(this);
    hide();
}

ProgsEdit::~ProgsEdit()
{
    delete ui;
}
void ProgsEdit::setlabel(QString str){
    setWindowTitle(str);
}
void ProgsEdit::setText(QString str){
    ui->edit->setPlainText(str);
}
void ProgsEdit::on_save_clicked(){
    FabriqueLitterale &f=FabriqueLitterale::getInstance();
    Programme *res= f.fabriquerProgramme(ui->edit->toPlainText());
    QHash<QString, Programme*>::iterator It=Controleur::getInstance().Progs.find(windowTitle());
    It.value()=res;
    ui->edit->clear();
    hide();
}
void ProgsEdit::on_cancel_clicked(){
    ui->edit->clear();
    hide();
}
