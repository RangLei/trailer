#-------------------------------------------------
#
# Project created by QtCreator 2014-09-22T16:42:57
#
#-------------------------------------------------

QT       -= core gui

TARGET = aio_handler
TEMPLATE = lib

DEFINES += AIO_HANDLER_LIBRARY

SOURCES += aio_handler.cpp

HEADERS += aio_handler.h\
        aio_handler_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
