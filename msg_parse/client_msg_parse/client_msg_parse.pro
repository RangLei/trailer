#-------------------------------------------------
#
# Project created by QtCreator 2014-09-20T14:02:57
#
#-------------------------------------------------

QT       -= core gui

macx:
{
    CONFIG-=app_bundle
    QMAKE_MAC_SDK = macosx10.10
}

TARGET = client_msg_parse
TEMPLATE = lib

DEFINES += CLIENT_MSG_PARSE_LIBRARY

INCLUDEPATH = ../..
DESTDIR = ../../lib

SOURCES += client_msg_parse.cpp

HEADERS += client_msg_parse.h

QMAKE_LEXFLAGS += -d
QMAKE_YACCFLAGS += -t

LEXSOURCES += client_msg.l
YACCSOURCES += client_msg.y

unix {
    target.path = /usr/lib
    INSTALLS += target
}
