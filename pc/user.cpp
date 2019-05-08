#include "user.h"

user *user::instance = NULL;
user::user()
{

}

user *user::get_instance(QString u, QString p, int role)
{
    if (instance == NULL)
    {
        instance = new user;
        instance->u = u;
        instance->p = p;
        instance->role = role;
    }

    return instance;
}

int user::get_role()
{
    return role;
}

QString user::get_pass()
{
    return p;
}

QString user::get_user()
{
    return u;
}
