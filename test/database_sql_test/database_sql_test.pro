TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = ../bin/database_sql_test

INCLUDEPATH += ../..
LIBS += -L../../lib -ldatabase_mysql
LIBS += -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -ldl


SOURCES += main.cpp
