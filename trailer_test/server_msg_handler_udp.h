#ifndef SERVER_MSG_HANDLER_UDP_H
#define SERVER_MSG_HANDLER_UDP_H

#include <ace/INET_Addr.h>
#include <ace/SOCK_Dgram.h>
#include <ace/Event_Handler.h>
#include <ace/Message_Block.h>
#include <ace/Singleton.h>

class Database_SQL;
class Server_Msg_Handler_UDP : public ACE_Event_Handler
{
public:
    Server_Msg_Handler_UDP();
    int init(int port, ACE_TCHAR *ip = NULL);
    void release();

    int open ();
    void close();

    int handle_input(ACE_HANDLE fd);
    int handle_close(ACE_HANDLE fd, ACE_Reactor_Mask mask);
    int send_message(ACE_INET_Addr const& remote_addr
                     , ACE_TCHAR const *msg
                     , int msg_len);
private:
    ACE_INET_Addr _local_addr;
    ACE_SOCK_Dgram _sock_dgram;
    ACE_Message_Block *_msg_block_recv;
    Database_SQL *_db_sql;
};

typedef ACE_Singleton<Server_Msg_Handler_UDP, ACE_Thread_Mutex> Server_Msg_Handler_UDP_Singleton;

#endif // SERVER_MSG_HANDLER_UDP_H
