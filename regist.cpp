#include "regist.h"
#include "ui_regist.h"
#include <iostream>

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

void regist::set_db(dboperate *db)
{
    this->db = db;
}

void regist::on_pushButton_clicked()
{
    QString user = ui->lineEdit->text();
    QString passwd1 = ui->lineEdit_2->text();
    QString passwd2 = ui->lineEdit_3->text();

    if (passwd1.compare(passwd2))
    {
        return;
    }

    if (db->add_user(user, passwd1))
    {
        this->close();
    }
}

void regist::on_pushButton_2_clicked()
{
    this->close();
}
