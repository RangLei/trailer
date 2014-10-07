#ifndef SERVER_MSG_PARSE_H
#define SERVER_MSG_PARSE_H

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

#if defined(SERVER_MSG_PARSE_LIBRARY)
#  define SERVER_MSG_PARSESHARED_EXPORT MY_DECL_EXPORT
#else
#  define SERVER_MSG_PARSESHARED_EXPORT MY_DECL_IMPORT
#endif

#include <iostream>
using namespace std;

#include "msg_handler/msg_handler.h"

int SERVER_MSG_PARSESHARED_EXPORT server_msg_parse(char *msg, int msg_len, Msg_Handler_Base *msg_handler);


#endif // SERVER_MSG_PARSE_H
