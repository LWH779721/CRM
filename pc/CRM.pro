#-------------------------------------------------
#
# Project created by QtCreator 2017-01-12T22:19:55
#
#-------------------------------------------------

QT       += core gui sql network #testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CRM
TEMPLATE = app


SOURCES += user.cpp\
    main.cpp\
    login.cpp \
    regist.cpp \
    dboperate.cpp \
    mainwindow.cpp \
    salesman.cpp \
    customer.cpp \
    deal.cpp \
    change_passwd.cpp \
    email.cpp \
    get_back_passwd.cpp

HEADERS  += user.h\
    login.h \
    regist.h \
    dboperate.h \
    mainwindow.h \
    salesman.h \
    customer.h \
    deal.h \
    change_passwd.h \
    email.h \
    get_back_passwd.h

FORMS    += login.ui \
    regist.ui \
    mainwindow.ui \
    salesman.ui \
    customer.ui \
    deal.ui \
    change_passwd.ui \
    get_back_passwd.ui

RC_FILE = resouce.rc

RESOURCES +=
