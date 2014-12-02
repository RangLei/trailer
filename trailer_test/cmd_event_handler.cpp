#include "cmd_event_handler.h"

Cmd_Event_Handler::Cmd_Event_Handler()
{
}

int Cmd_Event_Handler::open(void* acceptor_or_connector)
{
    int rc = Super::open(acceptor_or_connector);
    return rc;
}

int Cmd_Event_Handler::close(u_long flags)
{
    int rc = Super::close(flags);
    return rc;
}

int Cmd_Event_Handler::handle_send_message(const char* buf, int length)
{
    int rc = 0;
    return rc;
}

int Cmd_Event_Handler::handle_recv_message(const char* buf, int length)
{
    //TODO: chenpan
    int rc = 0;
    return rc;
}
