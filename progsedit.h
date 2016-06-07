#ifndef PROGSEDIT_H
#define PROGSEDIT_H

#include <QDialog>

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

private:
    Ui::ProgsEdit *descrip;
};

#endif // PROGSEDIT_H
