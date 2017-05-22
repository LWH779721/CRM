#ifndef GET_BACK_PASSWD_H
#define GET_BACK_PASSWD_H

#include <QDialog>
#include <QToolTip>
#include <QMessageBox>
#include "email.h"
#include "dboperate.h"

namespace Ui {
class get_back_passwd;
}

class get_back_passwd : public QDialog
{
    Q_OBJECT

public:
    explicit get_back_passwd(QWidget *parent = 0);
    ~get_back_passwd();

private slots:
    void on_pushButton_clicked();

private:
    Ui::get_back_passwd *ui;
};

#endif // GET_BACK_PASSWD_H
