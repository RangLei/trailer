#ifndef MP_PROTOCOL_CONNECTOR_H
#define MP_PROTOCOL_CONNECTOR_H

#include <ace/SOCK_Connector.h>
#include <ace/Reactor.h>
#include <ace/Connector.h>
#include <ace/SOCK_Stream.h>

template <class ACE_Protocol_Handler_Client>
class ACE_Protocol_Connector : public ACE_Connector<ACE_Protocol_Handler_Client, ACE_SOCK_CONNECTOR>
{
    typedef ACE_Connector<ACE_Protocol_Handler_Client, ACE_SOCK_CONNECTOR> Super;
public:
    ACE_Protocol_Connector();

    int init(ACE_INET_Addr remote_addr, time_t handler_timeout=2);

    void release();

protected:
    virtual int make_svc_handler (ACE_Protocol_Handler_Client *&sh);

private:

    time_t          _handler_timeout;
    ACE_INET_Addr   _remote_addr;
};

template <class ACE_Protocol_Handler_Client>
ACE_Protocol_Connector<ACE_Protocol_Handler_Client>::ACE_Protocol_Connector() : _handler_timeout(0)
{
}

template <class ACE_Protocol_Handler_Client>
int ACE_Protocol_Connector<ACE_Protocol_Handler_Client>::init(ACE_INET_Addr remote_addr, time_t handler_timeout)
{
    _remote_addr = remote_addr;
     _handler_timeout = handler_timeout;
     return 0;
}

template <class ACE_Protocol_Handler_Client>
void ACE_Protocol_Connector<ACE_Protocol_Handler_Client>::release()
{
}

template <class ACE_Protocol_Handler_Client>
int ACE_Protocol_Connector<ACE_Protocol_Handler_Client>::make_svc_handler (ACE_Protocol_Handler_Client *&sh)
{
    if(sh != NULL)
    {
        return Super::make_svc_handler(sh);
    }

    ACE_NEW_RETURN(sh, ACE_Protocol_Handler_Client, -1);

    sh->init(_remote_addr, _handler_timeout);

    ACE_Reactor *r = this->reactor();
    sh->reactor( r );

    return 0;
}

#endif // MP_PROTOCOL_CONNECTOR_H
