TEMPLATE = subdirs

macx:
{
    CONFIG-=app_bundle
    QMAKE_MAC_SDK = macosx10.10
}

SUBDIRS += \
    object \
    msg_parse

msg_parse.depands = object

