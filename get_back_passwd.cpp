#include "get_back_passwd.h"
#include "ui_get_back_passwd.h"

get_back_passwd::get_back_passwd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::get_back_passwd)
{
    ui->setupUi(this);
}

get_back_passwd::~get_back_passwd()
{
    delete ui;
}

void get_back_passwd::on_pushButton_clicked()
{
    QSqlQuery query;
    QString to = ui->lineEdit->text().trimmed();

    query.prepare("select passwd from user where mail = ?;");
    query.bindValue(0, to);
    query.exec();
    if (query.next())
    {
        QString passwd = query.value(0).toString();
        email::send(passwd,to);
        QMessageBox::information(this, "success", "邮件已发送！");
        this->close();
    }
    else
    {
        QMessageBox::information(this, "err", "邮箱未注册！");
    }
}
