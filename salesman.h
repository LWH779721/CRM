#ifndef SALESMAN_H
#define SALESMAN_H

#include <QDialog>
#include "dboperate.h"
#include <QMessageBox>

namespace Ui {
class salesman;
}

class salesman : public QDialog
{
    Q_OBJECT

public:
    int operate_flag; // 1:add ; 2:change
    int salesman_id; // salesman id for change
    explicit salesman(QWidget *parent = 0);
    ~salesman();
    void showEvent(QShowEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::salesman *ui;
};

#endif // SALESMAN_H
