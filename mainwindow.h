#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "dboperate.h"
#include "salesman.h"
#include "customer.h"
#include "deal.h"
#include "change_passwd.h"
#include "user.h"
#include "regist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void contextMenuEvent(QContextMenuEvent *event);
    void showEvent(QShowEvent *event);

private slots:
    void del();
    void add();
    void change();
    void change_upasswd();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    void load_salesman();
    void load_customerman();
    void load_deal();
    void load_user();
    Ui::MainWindow *ui;
    regist r;
    salesman s;
    customer c;
    deal d;
    QMenu *wpopupMenu;
    QAction *wdel;
    QAction *wadd;
    QAction *wchange;
    change_passwd *cpass;
};

#endif // MAINWINDOW_H
