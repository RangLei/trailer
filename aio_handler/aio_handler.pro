#-------------------------------------------------
#
# Project created by QtCreator 2014-09-22T16:42:57
#
#-------------------------------------------------

QT       -= core gui

TARGET = aio_handler
TEMPLATE = lib

DEFINES += AIO_HANDLER_LIBRARY
INCLUDEPATH += $(TOOLKITS)/include

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
