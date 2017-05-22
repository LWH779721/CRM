#include "customer.h"
#include "ui_customer.h"
#include <iostream>

customer::customer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::customer)
{
    ui->setupUi(this);
    QStringList status;
    status << tr("保密") << tr("男") << tr("女");
    ui->sex->addItems(status);
    status.clear();
    status << tr("保密") << tr("已婚") << tr("未婚");
    ui->comboBox_3->addItems(status);
    status.clear();
    status << tr("保密") << tr("是") << tr("否");
    ui->comboBox_5->addItems(status);
    ui->comboBox_6->addItems(status);
    ui->comboBox_8->addItems(status);
    ui->comboBox_9->addItems(status);
    ui->comboBox_10->addItems(status);
    ui->comboBox_11->addItems(status);
    ui->comboBox_13->addItems(status);
}

customer::~customer()
{
    delete ui;
}

void customer::showEvent(QShowEvent *event)
{
    if (this->operate_flag == 2)
    {
        QSqlQuery query;
        query.prepare("select * from customer where id = ?;");
        query.bindValue(0, this->customer_id);
        query.exec();
        if (query.next())
        {
            ui->lineEdit_2->setDisabled(1);
            ui->lineEdit_2->setText(query.value(1).toString());
            ui->sex->setCurrentText(query.value(2).toString());
            ui->comboBox_3->setCurrentText(query.value(3).toString());
            ui->ID->setText(query.value(4).toString());
            ui->comboBox_4->setCurrentText(query.value(6).toString());
            ui->phone->setText(query.value(7).toString());
            ui->lineEdit_5->setText(query.value(8).toString());
            ui->lineEdit_6->setText(query.value(9).toString());
            ui->comboBox_5->setCurrentText(query.value(10).toString());
            ui->comboBox_6->setCurrentText(query.value(11).toString());
            ui->comboBox_7->setCurrentText(query.value(12).toString());
            ui->textEdit_2->setText(query.value(13).toString());
            ui->lineEdit_8->setText(query.value(14).toString());
            ui->lineEdit_9->setText(query.value(15).toString());
            ui->lineEdit_10->setText(query.value(16).toString());
            ui->lineEdit_11->setText(query.value(17).toString());
            ui->lineEdit_12->setText(query.value(18).toString());
            ui->lineEdit_13->setText(query.value(19).toString());
            ui->lineEdit_14->setText(query.value(20).toString());
            ui->lineEdit_15->setText(query.value(21).toString());
            ui->textEdit->setText(query.value(22).toString());
            ui->comboBox_8->setCurrentText(query.value(23).toString());
            ui->comboBox_9->setCurrentText(query.value(24).toString());
            ui->comboBox_10->setCurrentText(query.value(25).toString());
            ui->lineEdit_17->setText(query.value(26).toString());
            ui->comboBox_11->setCurrentText(query.value(28).toString());
            ui->comboBox_12->setCurrentText(query.value(29).toString());
            ui->lineEdit_18->setText(query.value(30).toString());
            ui->comboBox_13->setCurrentText(query.value(31).toString());
            ui->lineEdit_19->setText(query.value(33).toString());
            ui->lineEdit_20->setText(query.value(34).toString());
            ui->lineEdit_21->setText(query.value(35).toString());

            ui->birth->setDate(query.value(5).toDate());
            ui->dateEdit_2->setDate(query.value(27).toDate());
            ui->dateEdit_3->setDate(query.value(32).toDate());
        }
        ui->pushButton->setText(tr("更改"));
    }
    else
    {
        ui->lineEdit_2->setDisabled(0);
        ui->lineEdit_2->clear();
        ui->ID->clear();
        ui->phone->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_8->clear();
        ui->lineEdit_9->clear();
        ui->lineEdit_10->clear();
        ui->lineEdit_11->clear();
        ui->lineEdit_12->clear();
        ui->lineEdit_13->clear();
        ui->lineEdit_14->clear();
        ui->lineEdit_15->clear();
        ui->lineEdit_17->clear();
        ui->lineEdit_18->clear();
        ui->lineEdit_19->clear();
        ui->lineEdit_20->clear();
        ui->lineEdit_21->clear();

        ui->sex->setCurrentIndex(0);
        ui->comboBox_3->setCurrentIndex(0);
        ui->comboBox_4->setCurrentIndex(0);
        ui->comboBox_5->setCurrentIndex(0);
        ui->comboBox_7->setCurrentIndex(0);
        ui->comboBox_8->setCurrentIndex(0);
        ui->comboBox_9->setCurrentIndex(0);
        ui->comboBox_10->setCurrentIndex(0);
        ui->comboBox_11->setCurrentIndex(0);
        ui->comboBox_12->setCurrentIndex(0);
        ui->comboBox_13->setCurrentIndex(0);

        ui->birth->setDate(QDate::fromString("2000/01/01", "yyyy/MM/dd"));
        ui->dateEdit_2->setDate(QDate::fromString("2000/01/01", "yyyy/MM/dd"));
        ui->dateEdit_3->setDate(QDate::fromString("2000/01/01", "yyyy/MM/dd"));

        ui->textEdit->clear();
        ui->textEdit_2->clear();
        ui->pushButton->setText(tr("确认"));
    }
}

void customer::on_pushButton_clicked()
{
    QSqlQuery query;

    if (this->operate_flag == 1)
    {
        query.prepare("insert into customer(name,sex,marriage,id_card,birthday,native,contact,address,company,sz,own_company,income,base_more,credit_lines,credit_debt,debtA_bank,debtA_bank_year_limit,debtA_bank_monery_sum,debtB_bank,debtB_bank_year_limit,debtB_bank_monery_sum,debt_more,szhouse,redpaper,mortgaged,mpayment,mpayment_day,own_car,car_year,car_value,own_policy,policy_date,policy_value,person_mflow,company_mflow) "
                "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        // base
        query.bindValue(0, ui->lineEdit_2->text());
        query.bindValue(1, ui->sex->currentText());
        query.bindValue(2, ui->comboBox_3->currentText());
        query.bindValue(3, ui->ID->text());
        query.bindValue(4, ui->birth->text());
        query.bindValue(5, ui->comboBox_4->currentText());
        query.bindValue(6, ui->phone->text());
        query.bindValue(7, ui->lineEdit_5->text());
        query.bindValue(8, ui->lineEdit_6->text());
        query.bindValue(9, ui->comboBox_5->currentText());
        query.bindValue(10, ui->comboBox_6->currentText());
        query.bindValue(11, ui->comboBox_7->currentText().toInt());
        query.bindValue(12, ui->textEdit_2->document()->toPlainText());
        // credit
        query.bindValue(13, ui->lineEdit_8->text().toInt());
        query.bindValue(14, ui->lineEdit_9->text().toInt());
        query.bindValue(15, ui->lineEdit_10->text());
        query.bindValue(16, ui->lineEdit_11->text().toInt());
        query.bindValue(17, ui->lineEdit_12->text().toInt());
        query.bindValue(18, ui->lineEdit_13->text());
        query.bindValue(19, ui->lineEdit_14->text().toInt());
        query.bindValue(20, ui->lineEdit_15->text().toInt());
        query.bindValue(21, ui->textEdit->document()->toPlainText());
        // value
        query.bindValue(22, ui->comboBox_8->currentText());
        query.bindValue(23, ui->comboBox_9->currentText());
        query.bindValue(24, ui->comboBox_10->currentText());
        query.bindValue(25, ui->lineEdit_17->text().toInt());
        query.bindValue(26, ui->dateEdit_2->text());
        query.bindValue(27, ui->comboBox_11->currentText());
        query.bindValue(28, ui->comboBox_12->currentText().toInt());
        query.bindValue(29, ui->lineEdit_18->text().toInt());
        query.bindValue(30, ui->comboBox_13->currentText());
        query.bindValue(31, ui->dateEdit_3->text());
        query.bindValue(32, ui->lineEdit_19->text().toInt());
        query.bindValue(33, ui->lineEdit_20->text().toInt());
        query.bindValue(34, ui->lineEdit_21->text().toInt());
    }
    else if (this->operate_flag == 2)
    {
        query.prepare("update customer set sex = ?,marriage = ?,id_card = ?,birthday = ?,native = ?,contact = ?,address = ?,company = ?,sz = ?,own_company = ?,income = ?,base_more = ?,credit_lines = ?,credit_debt = ?,debtA_bank = ?,debtA_bank_year_limit = ?,debtA_bank_monery_sum = ?,debtB_bank = ?,debtB_bank_year_limit = ?,debtB_bank_monery_sum = ?,debt_more = ?,szhouse = ?,redpaper = ?,mortgaged = ?,mpayment = ?,mpayment_day = ?,own_car = ?,car_year = ?,car_value = ?,own_policy = ?,policy_date = ?,policy_value = ?,person_mflow = ?,company_mflow = ? where name = ?;");
        // base
        query.bindValue(0, ui->sex->currentText());
        query.bindValue(1, ui->comboBox_3->currentText());
        query.bindValue(2, ui->ID->text());
        query.bindValue(3, ui->birth->text());
        query.bindValue(4, ui->comboBox_4->currentText());
        query.bindValue(5, ui->phone->text());
        query.bindValue(6, ui->lineEdit_5->text());
        query.bindValue(7, ui->lineEdit_6->text());
        query.bindValue(8, ui->comboBox_5->currentText());
        query.bindValue(9, ui->comboBox_6->currentText());
        query.bindValue(10, ui->comboBox_7->currentText().toInt());
        query.bindValue(11, ui->textEdit_2->document()->toPlainText());
        // credit
        query.bindValue(12, ui->lineEdit_8->text().toInt());
        query.bindValue(13, ui->lineEdit_9->text().toInt());
        query.bindValue(14, ui->lineEdit_10->text());
        query.bindValue(15, ui->lineEdit_11->text().toInt());
        query.bindValue(16, ui->lineEdit_12->text().toInt());
        query.bindValue(17, ui->lineEdit_13->text());
        query.bindValue(18, ui->lineEdit_14->text().toInt());
        query.bindValue(19, ui->lineEdit_15->text().toInt());
        query.bindValue(20, ui->textEdit->document()->toPlainText());
        // value
        query.bindValue(21, ui->comboBox_8->currentText());
        query.bindValue(22, ui->comboBox_9->currentText());
        query.bindValue(23, ui->comboBox_10->currentText());
        query.bindValue(24, ui->lineEdit_17->text().toInt());
        query.bindValue(25, ui->dateEdit_2->text());
        query.bindValue(26, ui->comboBox_11->currentText());
        query.bindValue(27, ui->comboBox_12->currentText().toInt());
        query.bindValue(28, ui->lineEdit_18->text().toInt());
        query.bindValue(29, ui->comboBox_13->currentText());
        query.bindValue(30, ui->dateEdit_3->text());
        query.bindValue(31, ui->lineEdit_19->text().toInt());
        query.bindValue(32, ui->lineEdit_20->text().toInt());
        query.bindValue(33, ui->lineEdit_21->text().toInt());

        query.bindValue(34, ui->lineEdit_2->text());
    }

    if (query.exec())
    {
        this->close();
    }
}

void customer::on_ID_editingFinished()
{
    QString id = ui->ID->text().trimmed();
    if (id.length() != 18)
    {
        QMessageBox::information(this, "Err", "身份证长度不对！ ");
        return;
    }

    QRegExp id_exp("[0-9]{17}[0-9,x,X]{1}");
    if (id_exp.exactMatch(id) == false)
    {
        QMessageBox::information(this, "Err", "身份证不对！ ");
        return;
    }

    QString birth = id.mid(6,8).insert(4,'/').insert(7,'/');
    ui->birth->setDate(QDate::fromString(birth, "yyyy/MM/dd"));

    if (id.at(16).cell()& 0x1)
    {
        ui->sex->setCurrentIndex(1);
    }
    else
    {
        ui->sex->setCurrentIndex(2);
    }
}

void customer::on_phone_editingFinished()
{
    QString phone = ui->phone->text().trimmed();
    QRegExp phone_exp("[0-9]{11}");

    if (phone_exp.exactMatch(phone) == false)
    {
        QMessageBox::information(this, "Err", "联系方式不对！ ");
        return;
    }
}
