#ifndef DBOPERATE_H
#define DBOPERATE_H

#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QString>

class dboperate
{
private:
    static dboperate *db;
    static QSqlDatabase m_dbconn;
    dboperate();
public:
    ~dboperate();
    static dboperate *instance();
};

#endif // DBOPERATE_H
