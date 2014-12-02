#ifndef CMD_EVENT_HANDLER_H
#define CMD_EVENT_HANDLER_H

#include "protocol/ace_protocol_server.h"

class Cmd_Event_Handler : public ACE_Protocol_Server
{
    typedef ACE_Protocol_Server Super;
public:
    Cmd_Event_Handler();

    virtual int open (void *acceptor_or_connector = 0);
    virtual int close(u_long flags);

    virtual int handle_recv_message(const char* buf, int length);
    virtual int handle_send_message(const char* buf, int length);

private:
    int _fd;
};

#endif // CMD_EVENT_HANDLER_H
