#include "regist.h"
#include "ui_regist.h"

regist::regist(QWidget *parent):
    QDialog(parent),
    ui(new Ui::regist)
{
    ui->setupUi(this);
}

regist::~regist()
{
    delete ui;
}

void regist::showEvent(QShowEvent *event)
{
    if (this->operate_flag == 2)
    {
        QSqlQuery query;
        query.prepare("select * from user where id = ?;");
        query.bindValue(0, this->user_id);
        query.exec();
        if (query.next())
        {
            ui->lineEdit->setDisabled(1);
            ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
            ui->label_4->hide();
            ui->lineEdit_3->hide();
            ui->lineEdit->setText(query.value(1).toString());
            ui->lineEdit_2->setText(query.value(3).toString());
            ui->lineEdit_4->setText(query.value(2).toString());
        }
        ui->pushButton->setText(tr("更改"));
    }
    else if (this->operate_flag == 1)
    {
        ui->lineEdit->setDisabled(0);
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
        ui->label_4->hide();
        ui->lineEdit_3->hide();
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_4->clear();
        ui->pushButton->setText(tr("确认"));
    }
}

void regist::on_pushButton_clicked()
{
    QString user = ui->lineEdit->text().trimmed();
    QString passwd1 = ui->lineEdit_2->text().trimmed();
    QString passwd2 = ui->lineEdit_3->text().trimmed();
    QString mail = ui->lineEdit_4->text().trimmed();
    QSqlQuery query;

    if (this->operate_flag == 2)
    {
        if (passwd1.length() == 0)
        {
            QToolTip::showText(ui->lineEdit_2->mapToGlobal(ui->lineEdit_2->mapFromParent(ui->lineEdit_2->pos())),"请输入密码！");
        }
        else if (mail.length() == 0)
        {
            QToolTip::showText(ui->lineEdit_4->mapToGlobal(ui->lineEdit_4->mapFromParent(ui->lineEdit_4->pos())),"请输入邮箱！");
        }
        else
        {
            query.prepare("update user set mail = ?,passwd = ? where name = ?;");
            query.bindValue(0, mail);
            query.bindValue(1, passwd1);
            query.bindValue(2, user);

            if (query.exec())
            {
                this->close();
            }
            else
            {
                QMessageBox::information(this, "Warm", "更改失败！");
            }
        }
    }
    else
    {
        if (user.length() == 0)
        {
            QToolTip::showText(ui->lineEdit->mapToGlobal(ui->lineEdit->mapFromParent(ui->lineEdit->pos())),"请输入帐号！");
        }
        else if (passwd1.length() == 0)
        {
            QToolTip::showText(ui->lineEdit_2->mapToGlobal(ui->lineEdit_2->mapFromParent(ui->lineEdit_2->pos())),"请输入密码！");
        }
        else if (mail.length() == 0)
        {
            QToolTip::showText(ui->lineEdit_4->mapToGlobal(ui->lineEdit_4->mapFromParent(ui->lineEdit_4->pos())),"请输入邮箱！");
        }
        else if (passwd1.compare(passwd2))
        {
            QToolTip::showText(ui->lineEdit_3->mapToGlobal(ui->lineEdit_3->mapFromParent(ui->lineEdit_3->pos())),"两次输入的密码不一致！");
        }
        else
        {
            query.prepare("insert into user(name,passwd,mail,role) values(?,?,?,1);");
            query.bindValue(0, user);
            query.bindValue(1, passwd1);
            query.bindValue(2, mail);

            if (query.exec())
            {
                this->close();
            }
            else
            {
                QMessageBox::information(this, "Warm", "帐号已存在！");
            }
        }
    }
}
