#ifndef IP_HANDLER_MAP_H
#define IP_HANDLER_MAP_H

#include <ace/Map_Manager.h>
#include <ace/Thread_Mutex.h>

#include <ace/Singleton.h>

class IP_Handler_Map : public
        ACE_Map_Manager<unsigned long,
        int,
        ACE_Thread_Mutex>
{
};

typedef ACE_Singleton<IP_Handler_Map, ACE_Thread_Mutex> IP_Handler_Map_Singleton;

#endif // IP_HANDLER_MAP_H
