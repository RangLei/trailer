TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../bin

macx {
    CONFIG-=app_bundle
    QMAKE_MAC_SDK = macosx10.10
}

macx {
    INCLUDEPATH += $(ACE_ROOT)
    LIBS += -L$(ACE_ROOT)/lib -lACE
}

!macx {
    INCLUDEPATH += $(TOOLKITS)/include
    LIBS += -L$(TOOLKITS)/lib -lACE
}

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += ..
LIBS += -L../lib -laio_handler -lserver_msg_parse -lmsg_handler -ldatabase_mysql
LIBS += -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -ldl

SOURCES += main.cpp \
    aio_server_msg_handler.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    aio_server_msg_handler.h

