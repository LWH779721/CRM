#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->label->installEventFilter(this);
    ui->label_2->installEventFilter(this);
    //QPalette plt;
    //plt.setBrush(QPalette::Window, QBrush(QPixmap(":/Sperdsheet/images/copy.png")));

    //plt.setColor (QPalette::Background, QColor (0, 0 , 0, 255));
    //plt.setColor (QPalette::Foreground, QColor (255,255,255,255));
    //this->setPalette(plt);
}

login::~login()
{
    delete ui;
}

bool login::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (obj == ui->label)
        {
            this->hide();
            re = new regist(this);
            re->show();
            re->exec();
            delete re;
            this->show();
        }
        else if (obj == ui->label_2)
        {
            this->hide();
            back = new get_back_passwd(this);
            back->show();
            back->exec();
            delete back;
            this->show();
        }

        return true;
    }

    return false;
}

void login::on_pushButton_clicked()
{
    QString u = ui->comboBox->currentText().trimmed();
    QString passwd = ui->lineEdit_2->text().trimmed();

    if (u.length() == 0)
    {
        QToolTip::showText(ui->comboBox->mapToGlobal(ui->comboBox->pos()),"请输入帐号！");
    }
    else if (passwd.length() == 0)
    {
        QToolTip::showText(ui->lineEdit_2->mapToGlobal(ui->comboBox->pos()),"请输入密码！");
    }
    else
    {
        QSqlQuery query;

        query.prepare("select * from user where name == ? and passwd = ?;");
        query.bindValue(0, u);
        query.bindValue(1, passwd);
        query.exec();

        if (query.next())
        {
            this->hide();
            user::get_instance(u, passwd, query.value(4).toInt());
            main.show();
            this->close();
        }
        else
        {
            QMessageBox::information(this, "Err", "登录失败");
        }
    }
}
