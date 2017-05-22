#include "salesman.h"
#include "ui_salesman.h"

salesman::salesman(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salesman)
{
    ui->setupUi(this);
}

salesman::~salesman()
{
    delete ui;
}

void salesman::showEvent(QShowEvent *event)
{
    if (this->operate_flag == 2)
    {
        QSqlQuery query;
        query.prepare("select * from salesman where id = ?;");
        query.bindValue(0, this->salesman_id);
        query.exec();
        if (query.next())
        {
            ui->lineEdit->setDisabled(1);
            ui->lineEdit->setText(query.value(1).toString());
            ui->lineEdit_2->setText(query.value(2).toString());
        }
        ui->pushButton->setText(tr("更改"));
    }
    else
    {
        ui->lineEdit->setDisabled(0);
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->pushButton->setText(tr("确认"));
    }
}

void salesman::on_pushButton_clicked()
{
    QSqlQuery query;

    if (this->operate_flag == 1)
    {
        query.prepare("insert into salesman(name,contact) values(?,?)");
        query.bindValue(0, ui->lineEdit->text());
        query.bindValue(1, ui->lineEdit_2->text());
    }
    else if (this->operate_flag == 2)
    {
        query.prepare("update salesman set contact = ? where name = ?;");
        query.bindValue(0, ui->lineEdit_2->text());
        query.bindValue(1, ui->lineEdit->text());
    }

    if (query.exec())
    {
        this->close();
    }
    else
    {
        QMessageBox::information(this, "Err", "用户已存在");
    }
}
