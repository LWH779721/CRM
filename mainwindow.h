#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dboperate.h"
#include "renew.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void set_db(dboperate *db);
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void del();
    void add();
    void change();

private:
    Ui::MainWindow *ui;
    renew wnew;
    dboperate *db;
    QMenu *wpopupMenu;
    QAction *wdel;
    QAction *wadd;
    QAction *wchange;
};

#endif // MAINWINDOW_H
