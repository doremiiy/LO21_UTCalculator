#include "progrsedit.h"
#include "ui_progrsedit.h"
#include "mainwindow.h"

ProgrsEdit::ProgrsEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgrsEdit)
{
    ui->setupUi(this);
    hide();
    connect(ui->cancel, SIGNAL(clicked()), parent, SLOT(saveProg()));
}

ProgrsEdit::~ProgrsEdit()
{
    delete ui;
}
void ProgrsEdit::setText(QString str){
    ui->edit->setPlainText(str);
}
/*void ProgrsEdit::on_save_clicked(){
    QString res= ui->edit->toPlainText();
    QHash<QString, Programme*>::iterator It=Controleur::getInstance().Progs.find();
}*/
void ProgrsEdit::on_cancel_clicked(){
    ui->edit->clear();
    hide();
}
