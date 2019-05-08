#ifndef USER_H
#define USER_H

#include <QString>

class user
{
private:
    static user *instance;
    QString p;
    QString u;
    int role;
    user();
public:
    static user *get_instance(QString u, QString p, int role);
    int get_role();
    QString get_pass();
    QString get_user();
};

#endif // USER_H
