#ifndef REGIST_H
#define REGIST_H

#include <QDialog>
#include "dboperate.h"

namespace Ui {
class regist;
}

class regist : public QDialog
{
    Q_OBJECT

public:
    explicit regist(QWidget *parent = 0);
    ~regist();
    void set_db(dboperate *db);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::regist *ui;
    dboperate *db;
};

#endif // REGIST_H
