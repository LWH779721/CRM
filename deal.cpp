#include "deal.h"
#include "ui_deal.h"

deal::deal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deal)
{
    QStringList status;
    ui->setupUi(this);
    status << tr("申请中") << tr("已通过") << tr("未通过");
    ui->comboBox_14->addItems(status);
    status.clear();
    status << tr("资料准备") << tr("银行面签") << tr("补资料") << tr("审批中") << tr("电核中") << tr("审批通过") << tr("等待放款") << tr("其他");
    ui->comboBox_17->addItems(status);
}

deal::~deal()
{
    delete ui;
}

void deal::showEvent(QShowEvent *event)
{
    QSqlQuery query;

    ui->comboBox->clear();
    ui->comboBox_2->clear();
    if (this->operate_flag == 2)
    {
        query.prepare("select * from deal where id = ?;");
        query.bindValue(0, this->deal_id);
        query.exec();
        if (query.next())
        {
            ui->dateTimeEdit->setDateTime(query.value(4).toDateTime());
            ui->comboBox->addItem(query.value(1).toString());
            ui->comboBox->setCurrentText(query.value(1).toString());
            ui->comboBox_2->addItem(query.value(2).toString());
            ui->comboBox_2->setCurrentText(query.value(2).toString());
            ui->comboBox->setEnabled(false);
            ui->comboBox_2->setEnabled(false);
            if (query.value(3).toString() == tr("申请中"))
            {
                ui->comboBox_14->setCurrentIndex(0);
                ui->lineEdit_22->setText(query.value(6).toString());
                ui->lineEdit_24->setText(query.value(7).toString());
                ui->comboBox_16->setCurrentText(query.value(5).toString());
                ui->comboBox_17->setCurrentText(query.value(8).toString());
                ui->textEdit_3->setText(query.value(9).toString());
            }
            else if (query.value(3).toString() == tr("已通过"))
            {
                ui->comboBox_14->setCurrentIndex(1);
                ui->lineEdit_22->setText(query.value(6).toString());
                ui->lineEdit_24->setText(query.value(7).toString());
                ui->comboBox_16->setCurrentText(query.value(5).toString());
                ui->comboBox_17->setCurrentText(query.value(8).toString());
                ui->textEdit_3->setText(query.value(9).toString());
                ui->lineEdit_25->setText(query.value(6).toString());
                ui->lineEdit_26->setText(query.value(10).toString());
                ui->lineEdit_27->setText(query.value(5).toString());
                ui->lineEdit_28->setText(query.value(12).toString());
                ui->lineEdit_29->setText(query.value(15).toString());
                ui->lineEdit_30->setText(query.value(14).toString());
                ui->textEdit_2->setText(query.value(16).toString());

                ui->dateEdit_4->setDate(query.value(11).toDate());
                ui->dateEdit_5->setDate(query.value(13).toDate());
            }
            else
            {
                ui->comboBox_14->setCurrentIndex(2);
                ui->lineEdit_22->setText(query.value(6).toString());
                ui->lineEdit_24->setText(query.value(7).toString());
                ui->comboBox_16->setCurrentText(query.value(5).toString());
                ui->comboBox_17->setCurrentText(query.value(8).toString());
                ui->textEdit_3->setText(query.value(9).toString());
                ui->lineEdit_25->setText(query.value(6).toString());
                ui->lineEdit_26->setText(query.value(10).toString());
                ui->lineEdit_27->setText(query.value(5).toString());
                ui->lineEdit_28->setText(query.value(12).toString());
                ui->lineEdit_29->setText(query.value(15).toString());
                ui->lineEdit_30->setText(query.value(14).toString());
                ui->textEdit_2->setText(query.value(16).toString());
                ui->lineEdit_31->setText(query.value(6).toString());
                ui->lineEdit_32->setText(query.value(12).toString());
                ui->lineEdit_33->setText(query.value(7).toString());
                ui->lineEdit_34->setText(query.value(17).toString());
                ui->textEdit->setText(query.value(19).toString());

                ui->dateEdit_4->setDate(query.value(11).toDate());
                ui->dateEdit_5->setDate(query.value(13).toDate());
                ui->dateEdit_6->setDate(query.value(18).toDate());
            }
        }

        ui->pushButton->setText(tr("更改"));
    }
    else
    {
        ui->comboBox->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
        ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
        query.prepare("select name from salesman;");
        query.exec();
        while (query.next())
        {
            ui->comboBox->addItem(query.value(0).toString());
        }

        query.prepare("select name from customer;");
        query.exec();
        while (query.next())
        {
            ui->comboBox_2->addItem(query.value(0).toString());
        }

        ui->comboBox_14->setCurrentIndex(0);
        ui->lineEdit_22->clear();
        ui->lineEdit_24->clear();
        ui->comboBox_16->setCurrentText("");
        ui->comboBox_17->setCurrentIndex(0);
        ui->textEdit_3->clear();
        ui->lineEdit_25->clear();
        ui->lineEdit_26->clear();
        ui->lineEdit_27->clear();
        ui->lineEdit_28->clear();
        ui->lineEdit_29->clear();
        ui->lineEdit_30->clear();
        ui->textEdit_2->clear();
        ui->lineEdit_31->clear();
        ui->lineEdit_32->clear();
        ui->lineEdit_33->clear();
        ui->lineEdit_34->clear();
        ui->textEdit->clear();

        ui->dateEdit_4->setDate(QDate::fromString("2000/01/01", "yyyy/MM/dd"));
        ui->dateEdit_5->setDate(QDate::fromString("2000/01/01", "yyyy/MM/dd"));
        ui->dateEdit_6->setDate(QDate::fromString("2000/01/01", "yyyy/MM/dd"));
        ui->pushButton->setText(tr("确认"));
    }
}

void deal::on_comboBox_14_currentIndexChanged(int index)
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

void deal::on_pushButton_clicked()
{
    QSqlQuery query;

    if (this->operate_flag == 1)
    {
        query.prepare("insert into deal(date,sname,cname,status,follow_man,apply_sum,bank,apply_status,apply_more) "
                "values(?,?,?,?,?,?,?,?,?)");
        // base
        query.bindValue(0, QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
        query.bindValue(1, ui->comboBox->currentText());
        query.bindValue(2, ui->comboBox_2->currentText());
        query.bindValue(3, ui->comboBox_14->currentText());
        query.bindValue(4, ui->lineEdit_22->text());
        query.bindValue(5, ui->lineEdit_24->text().toInt());
        query.bindValue(6, ui->comboBox_16->currentText());
        query.bindValue(7, ui->comboBox_17->currentText());
        query.bindValue(8, ui->textEdit_3->document()->toPlainText());
    }
    else if (this->operate_flag == 2)
    {
        if (ui->comboBox_14->currentIndex() == 0)
        {
            query.prepare("update deal set date = ?,status = ?,follow_man = ?,apply_sum = ?,bank = ?,apply_status = ?,apply_more = ? where id = ?;");
            query.bindValue(0, QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ss"));
            query.bindValue(1, ui->comboBox_14->currentText());
            query.bindValue(2, ui->lineEdit_22->text());
            query.bindValue(3, ui->lineEdit_24->text().toInt());
            query.bindValue(4, ui->comboBox_16->currentText());
            query.bindValue(5, ui->comboBox_17->currentText());
            query.bindValue(6, ui->textEdit_3->document()->toPlainText());
            query.bindValue(7, this->deal_id);
        }
        else if (ui->comboBox_14->currentIndex() == 1)
        {
            query.prepare("update deal set date = ?,status = ?,follow_man = ?,loan_sum = ?,loan_time = ?,require = ?,loan_year_limit = ?,loan_interest = ?,loan_mpay = ?,loan_more = ? where id = ?;");
            query.bindValue(0, QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ss"));
            query.bindValue(1, ui->comboBox_14->currentText());
            query.bindValue(2, ui->lineEdit_25->text());
            query.bindValue(3, ui->lineEdit_26->text().toInt());
            query.bindValue(4, ui->dateEdit_4->text());
            query.bindValue(5, ui->lineEdit_28->text());
            query.bindValue(6, ui->dateEdit_5->text());
            query.bindValue(7, ui->lineEdit_29->text());
            query.bindValue(8, ui->lineEdit_30->text().toInt());
            query.bindValue(9, ui->textEdit_2->document()->toPlainText());
            query.bindValue(10, this->deal_id);
        }
        else if (ui->comboBox_14->currentIndex() == 2)
        {
            query.prepare("update deal set date = ?,status = ?,follow_man = ?,require = ?,failed_reason = ?,failed_otime = ?,failed_more = ? where id = ?;");
            query.bindValue(0, QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ss"));
            query.bindValue(1, ui->comboBox_14->currentText());
            query.bindValue(2, ui->lineEdit_31->text());
            query.bindValue(3, ui->lineEdit_32->text());
            query.bindValue(4, ui->lineEdit_34->text());
            query.bindValue(5, ui->dateEdit_6->text());
            query.bindValue(6, ui->textEdit->document()->toPlainText());
            query.bindValue(7, this->deal_id);
        }
    }

    if (query.exec())
    {
        this->close();
    }
    else
    {
        QMessageBox::information(this, "Err", "更改失败");
    }
}
