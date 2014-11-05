#-------------------------------------------------
#
# Project created by QtCreator 2014-02-21T15:41:33
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ../../bin/protocol_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += ../../protocol

INCLUDEPATH += $(TOOLKITS)/include
INCLUDEPATH += ../../

LIBS += -L../../lib -lprotocol
LIBS += -L$(TOOLKITS)/lib -lACE

SOURCES += \
    main.cpp \
    auto_test.cpp


HEADERS += \
    auto_test.h

