#include "renew.h"
#include "ui_renew.h"
#include <iostream>

renew::renew(QWidget *parent):
    QDialog(parent),
    ui(new Ui::renew)
{
    ui->setupUi(this);
    QStringList status;
    status << tr("男") << tr("女");
    ui->comboBox_2->addItems(status);
    status.clear();
    status << tr("已婚") << tr("未婚");
    ui->comboBox_3->addItems(status);
    status.clear();
    status << tr("是") << tr("否");
    ui->comboBox_5->addItems(status);
    ui->comboBox_6->addItems(status);
    ui->comboBox_8->addItems(status);
    ui->comboBox_9->addItems(status);
    ui->comboBox_10->addItems(status);
    ui->comboBox_11->addItems(status);
    ui->comboBox_13->addItems(status);
    status.clear();
    status << tr("申请中") << tr("已通过") << tr("未通过");
    ui->comboBox_14->addItems(status);

    //this->setFixedSize(644,800);
}

renew::~renew()
{
    delete ui;
}

void renew::showEvent(QShowEvent *event)
{
    if (this->flag > 0)
    {

    }
}

void renew::set_db(dboperate *db)
{
    this->db = db;
}

void renew::on_comboBox_14_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->groupBox_6->show();
        ui->groupBox_7->hide();
        ui->groupBox_8->hide();
    }
    else if (index == 1)
    {
        ui->groupBox_6->hide();
        ui->groupBox_7->show();
        ui->groupBox_8->hide();
    }
    else if (index == 2)
    {
        ui->groupBox_6->hide();
        ui->groupBox_7->hide();
        ui->groupBox_8->show();
    }
}

void renew::on_pushButton_clicked()
{

}
