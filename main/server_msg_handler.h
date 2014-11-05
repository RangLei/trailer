#ifndef SERVER_MSG_HANDLER_H
#define SERVER_MSG_HANDLER_H

#include "protocol/ace_protocol_server.h"

class Database_SQL;
class Server_MSG_Handler : public ACE_Protocol_Server
{
    typedef ACE_Protocol_Server Super;
public:
    Server_MSG_Handler();

    virtual int open (void *acceptor_or_connector = 0);
    virtual int close(u_long flags);

    virtual int handle_recv_message(const char* buf, int length);
    virtual int handle_send_message(const char* buf, int length);

private:
    Database_SQL *_db_sql;
    ACE_UINT32 _remote_ip;
};

#endif // SERVER_MSG_HANDLER_H
