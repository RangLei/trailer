TEMPLATE = lib
CONFIG += console
#CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt
VERSION = 1.0.2

QMAKE_CXXFLAGS += -std=c++0x

TARGET = ../lib/protocol

INCLUDEPATH += $(TOOLKITS)/include
INCLUDEPATH += ../../common
LIBS += -L$(TOOLKITS)/lib -lACE


HEADERS += \
    ace_protocol_acceptor.h \
    ace_protocol_server.h \
    ace_protocol_connector.h \
    udp_socket.h

SOURCES += \
    ace_protocol_server.cpp
