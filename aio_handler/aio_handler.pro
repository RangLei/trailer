#-------------------------------------------------
#
# Project created by QtCreator 2014-09-22T16:42:57
#
#-------------------------------------------------

QT       -= core gui

TARGET = aio_handler
TEMPLATE = lib

DESTDIR = ../lib

DEFINES += AIO_HANDLER_LIBRARY

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

SOURCES += \
    aio_client_handler.cpp \
    aio_server_hanler.cpp

HEADERS += aio_handler.h\
    aio_acceptor.h \
    aio_connector.h \
    aio_client_handler.h \
    aio_server_handler.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
