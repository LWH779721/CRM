#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>
#include <QToolTip>
#include "dboperate.h"
#include "regist.h"
#include "get_back_passwd.h"
#include "mainwindow.h"
#include "user.h"

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
    regist *re;
    get_back_passwd *back;
    MainWindow main;
};

#endif // LOGIN_H
