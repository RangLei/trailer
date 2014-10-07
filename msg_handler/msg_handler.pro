#-------------------------------------------------
#
# Project created by QtCreator 2014-10-07T08:43:08
#
#-------------------------------------------------

QT       -= core gui

TARGET = msg_handler
TEMPLATE = lib

DEFINES += MSG_HANDLER_LIBRARY

SOURCES += msg_handler.cpp

HEADERS += msg_handler.h\
        msg_handler_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
