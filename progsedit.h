#ifndef PROGSEDIT_H
#define PROGSEDIT_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class ProgsEdit;
}

class ProgsEdit : public QDialog
{
    Q_OBJECT
    friend class MainWindow;

public:
    explicit ProgsEdit(QWidget *parent = 0);
    ~ProgsEdit();
    void setlabel(QString str);

private:
    Ui::ProgsEdit *ui;
public slots:
    void setText(QString str);
    void on_save_clicked();
    void on_cancel_clicked();
};

#endif // PROGSEDIT_H
