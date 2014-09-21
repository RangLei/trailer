#-------------------------------------------------
#
# Project created by QtCreator 2014-09-20T14:01:46
#
#-------------------------------------------------

QT       -= core gui

macx:
{
    CONFIG-=app_bundle
    QMAKE_MAC_SDK = macosx10.10
}

TARGET = server_msg_parse
TEMPLATE = lib

DEFINES += SERVER_MSG_PARSE_LIBRARY

INCLUDEPATH = ../..
DESTDIR = ../../lib

SOURCES += server_msg_parse.cpp

HEADERS += server_msg_parse.h

QMAKE_LEXFLAGS += -d
QMAKE_YACCFLAGS += -t

LEXSOURCES += server_msg.l
YACCSOURCES += server_msg.y

unix {
    target.path = /usr/lib
    INSTALLS += target
}
