TEMPLATE = subdirs

macx {
    CONFIG-=app_bundle
    QMAKE_MAC_SDK = macosx10.10
}

msg_parse.depands = object msg_handler

main.depands = database_mysql

SUBDIRS += \
    object \
    msg_parse \
    aio_handler \
    protocol \
    msg_handler \
    database_mysql \
    main



