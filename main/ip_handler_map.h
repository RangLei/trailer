#ifndef IP_AIO_HANDLER_MAP_H
#define IP_AIO_HANDLER_MAP_H

#include <ace/Map_Manager.h>
#include <ace/Thread_Mutex.h>
#include "aio_handler/aio_server_handler.h"

#include <ace/Singleton.h>

class IP_AIO_Handler_Map : public
        ACE_Map_Manager<unsigned long,
        AIO_Server_Handler*,
        ACE_Thread_Mutex>
{
};

typedef ACE_Singleton<IP_AIO_Handler_Map, ACE_Thread_Mutex> IP_AIO_Handler_Map_Singleton;

#endif // IP_AIO_HANDLER_MAP_H
