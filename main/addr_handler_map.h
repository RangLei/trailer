#ifndef IP_HANDLER_MAP_H
#define IP_HANDLER_MAP_H

#include <ace/INET_Addr.h>
#include <ace/Map_Manager.h>
#include <ace/Thread_Mutex.h>

#include <ace/Singleton.h>

class Addr_Handler_Map : public
        ACE_Map_Manager<ACE_INET_Addr,
        int,
        ACE_Thread_Mutex>
{
};

typedef ACE_Singleton<Addr_Handler_Map, ACE_Thread_Mutex> Addr_Handler_Map_Singleton;

#endif // IP_HANDLER_MAP_H
