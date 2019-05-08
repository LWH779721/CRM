#ifndef CHANGE_PASSWD_H
#define CHANGE_PASSWD_H

#include <QDialog>
#include "user.h"
#include <QToolTip>
#include <QMessageBox>
#include "dboperate.h"

namespace Ui {
class change_passwd;
}

class change_passwd : public QDialog
{
    Q_OBJECT

public:
    explicit change_passwd(QWidget *parent = 0);
    ~change_passwd();

private slots:
    void on_pushButton_clicked();

private:
    Ui::change_passwd *ui;
};

#endif // CHANGE_PASSWD_H
