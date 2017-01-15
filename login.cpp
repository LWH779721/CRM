#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login),db(new dboperate)
{
    ui->setupUi(this);
    ui->label->installEventFilter(this);
    re.set_db(db);
    main.set_db(db);
}

login::~login()
{
    delete ui;
    delete db;
}

bool login::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        this->hide();
        re.show();
        re.exec();
        this->show();
        return true;
    }

    return false;
}

void login::on_pushButton_clicked()
{
    QString user = ui->comboBox->currentText();
    QString passwd = ui->lineEdit_2->text();

    if (db->login(user, passwd))
    {
        this->hide();
        main.show();
        this->close();
    }
}
