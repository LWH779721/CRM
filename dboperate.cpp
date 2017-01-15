#include "dboperate.h"

dboperate::dboperate()
{
    QString file = "./database/all.db";
    m_dbconn = QSqlDatabase::addDatabase("QSQLITE");    //添加SQLite数据库驱动
    m_dbconn.setDatabaseName(file);                     //在工程目录新建一个mytest.db的文件
    if(!m_dbconn.open())
    {
        qDebug("open file failed!");
    }
}

dboperate::~dboperate()
{
    m_dbconn.close();
}

bool dboperate::login(QString &user, QString &passwd)
{
    QSqlQuery query;
    QVariant name(user);
    QVariant pass(passwd);

    query.prepare("select passwd from user where name == ? and passwd = ?;");
    query.bindValue(0, name);
    query.bindValue(1, pass);
    query.exec();

    return query.next();
}

bool dboperate::add_user(QString &user, QString &passwd)
{
    QSqlQuery query;
    QVariant name(user);
    QVariant pass(passwd);

    query.prepare("insert into user(name,passwd) values(?,?);");
    query.bindValue(0, name);
    query.bindValue(1, pass);

    return query.exec();
}
