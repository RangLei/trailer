TEMPLATE = subdirs

macx {
    CONFIG-=app_bundle
    QMAKE_MAC_SDK = macosx10.10
}

SUBDIRS += \
    server_msg_parse \
    client_msg_parse \
    msg_parse_test

msg_parse_test.depands = server_msg_parse client_msg_parse
