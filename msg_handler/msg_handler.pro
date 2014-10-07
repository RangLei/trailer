#-------------------------------------------------
#
# Project created by QtCreator 2014-10-07T08:43:08
#
#-------------------------------------------------

QT       -= core gui

TARGET = msg_handler
TEMPLATE = lib

DEFINES += MSG_HANDLER_LIBRARY

macx
{
    CONFIG-=app_bundle
    QMAKE_MAC_SDK = macosx10.10
}

macx
{
    INCLUDEPATH += $(ACE_ROOT)
    LIBS += -L$(ACE_ROOT)/lib -lACE
}

!macx
{
    INCLUDEPATH += $(TOOLKITS)/include
    LIBS += -L$(TOOLKITS)/lib -lACE
}

SOURCES += msg_handler.cpp

HEADERS += msg_handler.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
