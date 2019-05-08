#ifndef EMAIL_H
#define EMAIL_H

#include <QTcpSocket>

class email
{
private:
    email();
public:
    static long send(QString &passwd, QString &to);
};

#endif // EMAIL_H
