#include "salesman.h"
#include "ui_salesman.h"

salesman::salesman(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salesman)
{
    ui->setupUi(this);

    QRegExp regxp("[\u4e00-\u9fa5]*");
    ui->name->setValidator(new QRegExpValidator(regxp,this));
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
            ui->name->setDisabled(1);
            ui->name->setText(query.value(1).toString());
            ui->phone->setText(query.value(2).toString());
        }
        ui->pushButton->setText(tr("更改"));
    }
    else
    {
        ui->name->setDisabled(0);
        ui->name->clear();
        ui->phone->clear();
        ui->pushButton->setText(tr("确认"));
    }
}

void salesman::on_pushButton_clicked()
{
    QSqlQuery query;

    if (this->operate_flag == 1)
    {
        query.prepare("insert into salesman(name,contact) values(?,?)");
        query.bindValue(0, ui->name->text());
        query.bindValue(1, ui->phone->text());
    }
    else if (this->operate_flag == 2)
    {
        query.prepare("update salesman set contact = ? where name = ?;");
        query.bindValue(0, ui->phone->text());
        query.bindValue(1, ui->name->text());
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

void salesman::on_phone_editingFinished()
{
    QString phone = ui->phone->text().trimmed();
    QRegExp phone_exp("[0-9]{11}");

    if (phone_exp.exactMatch(phone) == false)
    {
        QMessageBox::information(this, "Err", "联系方式不对！ ");
        return;
    }
}
