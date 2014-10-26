#-------------------------------------------------
#
# Project created by QtCreator 2014-10-26T01:06:15
#
#-------------------------------------------------

QT       -= core gui

TARGET = ../lib/database_mysql
TEMPLATE = lib

DEFINES += DATABASE_MYSQL_LIBRARY

SOURCES += \
    database_sql.cpp \
    database_sql_impl.cpp

HEADERS += \
    database_sql.h \
    database_sql_impl.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
