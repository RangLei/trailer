#ifndef MSG_HANDLER_H
#define MSG_HANDLER_H

#  ifndef MY_DECL
#  define MY_DECL

#  ifdef __WIN32__
#    define MY_DECL_EXPORT     __declspec(dllexport)
#    define MY_DECL_IMPORT     __declspec(dllimport)
#  else
#    define MY_DECL_EXPORT     __attribute__((visibility("default")))
#    define MY_DECL_IMPORT     __attribute__((visibility("default")))
#    define MY_DECL_HIDDEN     __attribute__((visibility("hidden")))
#  endif

#  endif

#if defined(OBJECT_LIBRARY)
#  define MSG_HANDLERSHARED_EXPORT MY_DECL_EXPORT
#else
#  define MSG_HANDLERSHARED_EXPORT MY_DECL_IMPORT
#endif


class MSG_HANDLERSHARED_EXPORT Msg_Handler_Base
{
public:
    virtual int handle(){return 0;}
};

template <class MSG>
class MSG_HANDLERSHARED_EXPORT Msg_Handler : public Msg_Handler_Base
{
public:
    int handle(){return 0;}
};

#endif // MSG_HANDLER_H
