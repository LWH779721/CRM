#ifndef DBOPERATE_H
#define DBOPERATE_H

#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QString>

class dboperate
{
private:
    QSqlDatabase m_dbconn;
public:
    dboperate();
    ~dboperate();

    bool add_user(QString &user, QString &passwd);
    bool login(QString &user, QString &passwd);
};

#endif // DBOPERATE_H
