#ifndef IP_HANDLER_MAP_H
#define IP_HANDLER_MAP_H

#include <list>
#include <ace/INET_Addr.h>
#include <ace/Map_Manager.h>
#include <ace/Vector_T.h>
#include <ace/Thread_Mutex.h>

#include <ace/Singleton.h>
#include <ace/Guard_T.h>
#include "server_msg_handler.h"

class Addr_Handler_Map : public
        ACE_Map_Manager<ACE_INET_Addr,
        int,
        ACE_Thread_Mutex>
{
};

typedef ACE_Singleton<Addr_Handler_Map, ACE_Thread_Mutex> Addr_Handler_Map_Singleton;

class Server_MSG_Handler;
class Server_MSG_Handler_List{
public:
    inline void push_handler(Server_MSG_Handler* node)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(_mutex);
        _handlers.push_back(node);
    }

    inline void erase_handler(Server_MSG_Handler* node)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(_mutex);
        for (auto iter = _handlers.begin();
             iter != _handlers.end(); )
        {
            if (node == *iter)
            {
                _handlers.erase(iter++);
                continue;
            }
            ++iter;
        }
    }

    inline void clear_handler()
    {
        ACE_Guard<ACE_Thread_Mutex> guard(_mutex);
        _handlers.clear();
    }

    void handler_func(const char* buf, int& length)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(_mutex);
        for (auto iter = _handlers.begin();
             iter != _handlers.end(); ++iter)
        {
            (*iter)->handle_send_message(buf, length);
        }
    }

private:
    std::list<Server_MSG_Handler*> _handlers;
    ACE_Thread_Mutex _mutex;

};


typedef ACE_Singleton<Server_MSG_Handler_List, ACE_Thread_Mutex> Handler_List_Singleton;


#endif // IP_HANDLER_MAP_H
