#-------------------------------------------------
#
# Project created by QtCreator 2014-09-17T23:31:24
#
#-------------------------------------------------

QT       -= gui

macx {
    CONFIG-=app_bundle
    QMAKE_MAC_SDK = macosx10.10
}

DESTDIR = ../lib

TARGET = object
TEMPLATE = lib

DEFINES += OBJECT_LIBRARY

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += object.cpp

HEADERS += object.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
