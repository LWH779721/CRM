#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    cpass = NULL;
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint); // 设置隐藏掉最大化按键
    this->setWindowState(Qt::WindowMaximized); //设置窗口最大化

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList combox2;
    combox2 << tr("业务员") << tr("客户") << tr("贷款记录") << tr("用户");
    ui->comboBox_2->addItems(combox2);

    this->wpopupMenu = new QMenu();  //创建主菜单
    this->wdel = wpopupMenu->addAction(tr("删除"));
    this->wadd = wpopupMenu->addAction(tr("新增"));
    this->wchange = wpopupMenu->addAction(tr("查看详细"));
    connect(wdel, SIGNAL(triggered(bool)), this, SLOT(del()));
    connect(wadd, SIGNAL(triggered(bool)), this, SLOT(add()));
    connect(wchange, SIGNAL(triggered(bool)), this, SLOT(change()));
    connect(ui->action, SIGNAL(triggered(bool)), this, SLOT(change_upasswd()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event)
{
    if (user::get_instance(NULL,NULL,0)->get_role() == 1)
    {
        ui->comboBox_2->removeItem(3);
    }
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    wpopupMenu->move(cursor().pos());
    wpopupMenu->show();
}

void MainWindow::del()
{
    int i = ui->tableWidget->currentRow();

    if ((i >= 0)
          && (QMessageBox::Yes == QMessageBox::warning(this,tr("Warm"),tr("Are you sure?"),QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes)))
    {
        QSqlQuery query;
        int j = ui->comboBox_2->currentIndex();

        if (j == 0)
        {
            query.prepare("delete from salesman where id = ?");
            query.bindValue(0, ui->tableWidget->item(i,0)->text());
        }
        else if (j == 1)
        {
            query.prepare("delete from customer where id = ?");
            query.bindValue(0, ui->tableWidget->item(i,0)->text());
        }
        else if (j == 2)
        {
            query.prepare("delete from deal where id = ?");
            query.bindValue(0, ui->tableWidget->item(i,0)->text());
        }
        else
        {
            if (ui->tableWidget->item(i,4)->text().compare("管理员") == 0)
            {
                QMessageBox::information(this, "Err", "不能删除管理员");
                return;
            }

            query.prepare("delete from user where id = ?");
            query.bindValue(0, ui->tableWidget->item(i,0)->text());
        }

        if (query.exec())
        {
            ui->tableWidget->removeRow(i);
        }
    }
}

void MainWindow::add()
{
    this->hide();
    int i = ui->comboBox_2->currentIndex();
    if (i == 0)
    {
        s.operate_flag = 1;
        s.show();
        s.exec();
        load_salesman();
    }
    else if (i == 1)
    {
        c.operate_flag = 1;
        c.show();
        c.exec();
        load_customerman();
    }
    else if (i == 2)
    {
        d.operate_flag = 1;
        d.show();
        d.exec();
        load_deal();
    }
    else
    {
        r.operate_flag = 1;
        r.show();
        r.exec();
        load_user();
    }

    this->show();
}

void MainWindow::change_upasswd()
{
    cpass = new change_passwd(this);
    cpass->show();
    cpass->exec();
    delete cpass;
    this->show();
}

void MainWindow::change()
{
    this->hide();
    int i = ui->comboBox_2->currentIndex();
    if (i == 0)
    {
        s.operate_flag = 2;
        s.salesman_id = ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().toInt();
        s.show();
        s.exec();
        load_salesman();
    }
    else if (i == 1)
    {
        c.operate_flag = 2;
        c.customer_id = ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().toInt();
        c.show();
        c.exec();
        load_customerman();
    }
    else if (i == 2)
    {
        d.operate_flag = 2;
        d.deal_id = ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().toInt();
        d.show();
        d.exec();
        load_deal();
    }
    else if (i == 3)
    {
        r.operate_flag = 2;
        r.user_id = ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().toInt();
        r.show();
        r.exec();
        load_user();
    }

    this->show();
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    if (index == 0)
    {
        load_salesman();
    }
    else if (index == 1)
    {
        load_customerman();
    }
    else if (index == 2)
    {
        load_deal();
    }
    else
    {
        load_user();
    }
}

void MainWindow::load_user()
{
    QStringList combox1;
    QSqlQuery query;
    int i = 0;

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();

    combox1 << tr("用户名") << tr("邮箱");
    ui->comboBox->clear();
    ui->comboBox->addItems(combox1);
    combox1.clear();
    combox1 << tr("ID") << tr("用户名") << tr("密码") << tr("邮箱") << tr("角色");
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(combox1);
    ui->tableWidget->setColumnHidden(0,1);
    query.prepare("select * from user");
    query.exec();

    while(query.next())
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value(4).toInt()?tr("普通用户"):tr("管理员")));
        i++;
    }
}

void MainWindow::load_salesman()
{
    QStringList combox1;
    QSqlQuery query;
    int i = 0;

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();

    combox1 << tr("姓名") << tr("联系方式");
    ui->comboBox->clear();
    ui->comboBox->addItems(combox1);
    combox1.clear();
    combox1 << tr("ID") << tr("姓名") << tr("联系方式");
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(combox1);
    ui->tableWidget->setColumnHidden(0,1);
    query.prepare("select * from salesman");
    query.exec();

    while(query.next())
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        i++;
    }
}

void MainWindow::load_customerman()
{
    QStringList combox1;
    QSqlQuery query;
    int i = 0;

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();
    combox1 << tr("姓名") << tr("生日");
    ui->comboBox->clear();
    ui->comboBox->addItems(combox1);
    combox1.clear();
    combox1 << tr("ID") << tr("姓名") << tr("性别") << tr("婚姻状况") << tr("身份证号码") << tr("生日") << tr("联系方式");
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(combox1);
    ui->tableWidget->setColumnHidden(0,1);
    query.prepare("select * from customer");
    query.exec();

    while(query.next())
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(query.value(5).toString()));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(query.value(7).toString()));
        i++;
    }
}

void MainWindow::load_deal()
{
    QStringList header;
    QSqlQuery query;
    int i = 0;

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();
    header << tr("业务员") << tr("客户") << tr("状态");
    ui->comboBox->clear();
    ui->comboBox->addItems(header);
    header.clear();
    header << tr("ID") << tr("日期") << tr("业务员") << tr("客户") << tr("状态") << tr("贷款银行") << tr("贷款金额");
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setColumnHidden(0,1);
    query.prepare("select * from deal order by date desc");
    query.exec();

    while(query.next())
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(query.value(5).toString()));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(query.value(7).toString()));
        i++;
    }
}

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    int i = ui->comboBox_2->currentIndex();
    int j = ui->comboBox->currentIndex();
    int k = 0;

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();
    if (i == 0)
    {
        if (j == 0)
        {
            query.prepare("select * from salesman where name like ?;");
        }
        else if (j == 1)
        {
            query.prepare("select * from salesman where contact like ?;");
        }

        query.bindValue(0,ui->lineEdit->text().prepend('%').append('%'));
        query.exec();

        while(query.next())
        {
            ui->tableWidget->insertRow(k);
            ui->tableWidget->setItem(k,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(k,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(k,2,new QTableWidgetItem(query.value(2).toString()));
            k++;
        }
    }
    else if (i == 1)
    {
        if (j == 0)
        {
            query.prepare("select * from customer where name like ?;");
        }
        else if (j == 1)
        {
            query.prepare("select * from customer where birthday like ?;");
        }

        query.bindValue(0,ui->lineEdit->text().prepend('%').append('%'));
        query.exec();

        while(query.next())
        {
            ui->tableWidget->insertRow(k);
            ui->tableWidget->setItem(k,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(k,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(k,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(k,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget->setItem(k,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget->setItem(k,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidget->setItem(k,6,new QTableWidgetItem(query.value(7).toString()));
            k++;
        }
    }
    else if (i == 2)
    {
        if (j == 0)
        {
            query.prepare("select * from deal where sname like ? order by date desc;");
        }
        else if (j == 1)
        {
            query.prepare("select * from deal where cname like ? order by date desc;");
        }
        else
        {
            query.prepare("select * from deal where status like ? order by date desc;");
        }

        query.bindValue(0,ui->lineEdit->text().prepend('%').append('%'));
        query.exec();

        while(query.next())
        {
            ui->tableWidget->insertRow(k);
            ui->tableWidget->setItem(k,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(k,1,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget->setItem(k,2,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(k,3,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(k,4,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget->setItem(k,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidget->setItem(k,6,new QTableWidgetItem(query.value(7).toString()));
            k++;
        }
    }
    else if (i == 3)
    {
        if (j == 0)
        {
            query.prepare("select * from user where name like ?;");
        }
        else if (j == 1)
        {
            query.prepare("select * from user where mail like ?;");
        }

        query.bindValue(0,ui->lineEdit->text().prepend('%').append('%'));
        query.exec();

        while(query.next())
        {
            ui->tableWidget->insertRow(k);
            ui->tableWidget->setItem(k,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(k,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(k,2,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget->setItem(k,3,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(k,4,new QTableWidgetItem(query.value(4).toInt()?tr("普通用户"):tr("管理员")));
            k++;
        }
    }
}

void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    change();
}
