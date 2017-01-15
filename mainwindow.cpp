#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    long i;
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint); // 设置隐藏掉最大化按键
    this->setWindowState(Qt::WindowMaximized); //设置窗口最大化

    QStringList combox1;
    combox1 << tr("ALL") << tr("申请中") << tr("已通过") << tr("未通过");
    ui->comboBox->addItems(combox1);
    QStringList combox2;
    combox2 << tr("ALL") << tr("客户姓名") << tr("业务员姓名");
    ui->comboBox_2->addItems(combox2);

    this->wpopupMenu = new QMenu();  //创建主菜单
    this->wdel = wpopupMenu->addAction(tr("删除"));
    this->wadd = wpopupMenu->addAction(tr("新建"));
    this->wchange = wpopupMenu->addAction(tr("修改"));
    connect(wdel, SIGNAL(triggered(bool)), this, SLOT(del()));
    connect(wadd, SIGNAL(triggered(bool)), this, SLOT(add()));
    connect(wchange, SIGNAL(triggered(bool)), this, SLOT(change()));
    wnew.set_db(db);

    QStringList header;
    header <<"ID"<<"业务员"<<"联系方式";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (i = 0; i < 10; i++)
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem("2017"));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem("test"));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_db(dboperate *db)
{
    this->db = db;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    wpopupMenu->move(cursor().pos());
    wpopupMenu->show();
}

void MainWindow::del()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

void MainWindow::add()
{
    this->hide();
    wnew.flag = -1;
    wnew.show();
    wnew.exec();
    this->show();
}

void MainWindow::change()
{
    this->hide();
    wnew.flag = 1;
    wnew.show();
    wnew.exec();
    this->show();
}
