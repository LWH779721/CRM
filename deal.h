#ifndef DEAL_H
#define DEAL_H

#include <QDialog>
#include <QMessageBox>
#include "dboperate.h"

namespace Ui {
class deal;
}

class deal : public QDialog
{
    Q_OBJECT

public:
    int operate_flag; // 1:add ; 2:change
    int deal_id;
    explicit deal(QWidget *parent = 0);
    ~deal();
    void showEvent(QShowEvent *event);

private slots:
    void on_comboBox_14_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::deal *ui;
};

#endif // DEAL_H
