#include <iostream>
#include "cmd_event_handler.h"
#include "addr_handler_map.h"

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
    std::cout << "handle_recv_message: " << buf << std::endl;
    Server_MSG_Handler_List *handler_list =
            Handler_List_Singleton::instance();

    handler_list->handler_func(buf, length);

    return 0;
}
