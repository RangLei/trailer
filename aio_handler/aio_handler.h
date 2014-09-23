#ifndef AIO_HANDLER_H
#define AIO_HANDLER_H

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
#  define AIO_HANDLERSHARED_EXPORT MY_DECL_EXPORT
#else
#  define AIO_HANDLERSHARED_EXPORT MY_DECL_IMPORT
#endif

template <class HANDLER> class AIO_HANDLERSHARED_EXPORT AIO_Acceptor;
template <class HANDLER> class AIO_HANDLERSHARED_EXPORT AIO_Connector;
class AIO_HANDLERSHARED_EXPORT AIO_Server_Handler;
class AIO_HANDLERSHARED_EXPORT AIO_Client_Handler;

#include "aio_acceptor.h"
#include "aio_connector.h"
#include "aio_server_handler.h"
#include "aio_client_handler.h"

#endif // AIO_HANDLER_H
