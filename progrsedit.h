#ifndef PROGRSEDIT_H
#define PROGRSEDIT_H

#include <QWidget>

namespace Ui {
class ProgrsEdit;
}

class ProgrsEdit : public QWidget
{
    Q_OBJECT
    friend class MainWindow;
public:
    explicit ProgrsEdit(QWidget *parent = 0);
    ~ProgrsEdit();

private:
    Ui::ProgrsEdit *ui;
public slots:
    void setText(QString str);
    //void on_save_clicked();
    void on_cancel_clicked();

};

#endif // PROGRSEDIT_H
