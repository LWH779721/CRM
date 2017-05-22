#include "dboperate.h"

dboperate * dboperate::db = NULL;
QSqlDatabase dboperate::m_dbconn;

dboperate::dboperate()
{
}

dboperate::~dboperate()
{
    m_dbconn.close();
}

dboperate *dboperate::instance()
{
    if (db == NULL)
    {
        QString file = "./database/all.db";
        m_dbconn = QSqlDatabase::addDatabase("QSQLITE");    //添加SQLite数据库驱动
        m_dbconn.setDatabaseName(file);                     //在工程目录新建一个mytest.db的文件
        if(!m_dbconn.open())
        {
            qDebug("open file failed!");
        }
    }

    return db;
}
