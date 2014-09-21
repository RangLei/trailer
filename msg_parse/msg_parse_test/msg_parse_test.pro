TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

macx:
{
    CONFIG-=app_bundle
    QMAKE_MAC_SDK = macosx10.10
}

DESTDIR = ../../bin

INCLUDEPATH = ../..
LIBS += -L../../lib -lobject -lserver_msg_parse -lclient_msg_parse

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

