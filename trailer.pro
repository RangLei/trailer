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
    database_mysql

msg_parse.depands = object msg_handler

main.depands = database_mysql
