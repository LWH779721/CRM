#ifndef RENEW_H
#define RENEW_H

#include <QDialog>
#include "dboperate.h"

namespace Ui {
class renew;
}

class renew : public QDialog
{
    Q_OBJECT

public:
    int flag;
    explicit renew(QWidget *parent = 0);
    ~renew();
    void set_db(dboperate *db);
    void showEvent(QShowEvent *event);

private slots:
    void on_comboBox_14_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::renew *ui;
    dboperate *db;
};

#endif // RENEW_H
