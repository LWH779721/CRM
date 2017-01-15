#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "dboperate.h"
#include "regist.h"
#include "mainwindow.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
protected:
    bool eventFilter(QObject *obj, QEvent *ev);
private slots:
    void on_pushButton_clicked();
private:
    Ui::login *ui;
    regist re;
    MainWindow main;
    dboperate *db;
};

#endif // LOGIN_H
