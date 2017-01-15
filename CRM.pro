#-------------------------------------------------
#
# Project created by QtCreator 2017-01-12T22:19:55
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CRM
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    regist.cpp \
    dboperate.cpp \
    mainwindow.cpp \
    renew.cpp

HEADERS  += login.h \
    regist.h \
    dboperate.h \
    mainwindow.h \
    renew.h

FORMS    += login.ui \
    regist.ui \
    mainwindow.ui \
    renew.ui
