#include "change_passwd.h"
#include "ui_change_passwd.h"

change_passwd::change_passwd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_passwd)
{
    ui->setupUi(this);
}

change_passwd::~change_passwd()
{
    delete ui;
}

void change_passwd::on_pushButton_clicked()
{
    QString opass = ui->lineEdit->text().trimmed();
    QString npass1 = ui->lineEdit_2->text().trimmed();
    QString npass2 = ui->lineEdit_3->text().trimmed();
    user *u = user::get_instance(NULL,NULL,0);

    if (opass.length() == 0)
    {
        QToolTip::showText(ui->lineEdit->mapToGlobal(ui->lineEdit->mapFromParent(ui->lineEdit->pos())),"请输入原密码！");
    }
    else if (npass1.length() == 0)
    {
        QToolTip::showText(ui->lineEdit_2->mapToGlobal(ui->lineEdit_2->mapFromParent(ui->lineEdit_2->pos())),"请输入新密码！");
    }
    else if (npass2.length() == 0)
    {
        QToolTip::showText(ui->lineEdit_3->mapToGlobal(ui->lineEdit_3->mapFromParent(ui->lineEdit_3->pos())),"请重新输入密码！");
    }
    else if (npass1.compare(npass2))
    {
        QToolTip::showText(ui->lineEdit_3->mapToGlobal(ui->lineEdit_3->mapFromParent(ui->lineEdit_3->pos())),"两次密码输入不一致！");
    }
    else if (opass.compare(u->get_pass()))
    {
        QToolTip::showText(ui->lineEdit->mapToGlobal(ui->lineEdit->mapFromParent(ui->lineEdit->pos())),"原密码错误！");
    }
    else
    {
        QSqlQuery query;

        query.prepare("update user set passwd = ? where name = ?;");
        query.bindValue(0, ui->lineEdit_2->text());
        query.bindValue(1, u->get_user());

        if (query.exec())
        {
            this->close();
        }
        else
        {
            QMessageBox::information(this, "Warm", "更改失败");
        }
    }
}
