#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QDialog>
#include "dboperate.h"
#include <QMessageBox>

namespace Ui {
class customer;
}

class customer : public QDialog
{
    Q_OBJECT

public:
    int operate_flag; // 1:add ; 2:change
    int customer_id; // customer id for change
    explicit customer(QWidget *parent = 0);
    ~customer();
    void showEvent(QShowEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_ID_editingFinished();

    void on_phone_editingFinished();

private:
    Ui::customer *ui;
};

#endif // CUSTOMER_H
