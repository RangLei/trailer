TEMPLATE = subdirs

macx {
    CONFIG-=app_bundle
    QMAKE_MAC_SDK = macosx10.10
}

SUBDIRS += \
    object \
    msg_parse \
    aio_handler \
    protocol \
    msg_handler \
    main \
    database_mysql \
    test

msg_parse.depands = object msg_handler

