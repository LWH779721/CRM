#ifndef REGIST_H
#define REGIST_H

#include <QDialog>
#include <QMessageBox>
#include <QToolTip>
#include "dboperate.h"

namespace Ui {
class regist;
}

class regist : public QDialog
{
    Q_OBJECT

public:
    int operate_flag; // 1:add ; 2:change
    int user_id; // salesman id for change
    explicit regist(QWidget *parent = 0);
    ~regist();
    void showEvent(QShowEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::regist *ui;
};

#endif // REGIST_H
