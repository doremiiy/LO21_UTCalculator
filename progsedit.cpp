#include "progsedit.h"
#include "ui_progsedit.h"

ProgsEdit::ProgsEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgsEdit)
{
    ui->setupUi(this);
}

ProgsEdit::~ProgsEdit()
{
    delete ui;
}
