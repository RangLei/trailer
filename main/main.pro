TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = trailer
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
LIBS += -L../lib -lprotocol -lserver_msg_parse -lmsg_handler -ldatabase_mysql -lobject
#LIBS += -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lmysqld -lpthread -lz -lm -ldl
LIBS += -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -ldl

SOURCES += main.cpp \
    cmd_down_from_db.cpp \
    server_msg_handler.cpp \
    server_msg_handler_udp.cpp \
    addr_handler_map.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    cmd_down_from_db.h \
    server_msg_handler.h \
    server_msg_handler_udp.h \
    addr_handler_map.h

