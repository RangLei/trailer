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

SERVER_MSG_PARSESHARED_EXPORT int server_msg_parse(const char* msg, const int msg_length);

#endif // SERVER_MSG_PARSE_H
