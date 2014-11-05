#ifndef ACE_PROTOCOL_ACCEPTOR_H
#define ACE_PROTOCOL_ACCEPTOR_H

#include <ace/SOCK_Acceptor.h>
#include <ace/Reactor.h>
#include <ace/Acceptor.h>
#include <ace/SOCK_Stream.h>
#include <ace/Singleton.h>
#include <ace/Thread_Mutex.h>

template <class ACE_Protocol_Server>
class ACE_Protocol_Acceptor : public ACE_Acceptor<ACE_Protocol_Server, ACE_SOCK_ACCEPTOR>
{
public:
    ACE_Protocol_Acceptor();

    int init(time_t handler_timeout=2);
    void release();

    //protected:
    virtual int make_svc_handler (ACE_Protocol_Server *&sh);

private:
    time_t _handler_timeout;
};

template <class ACE_Protocol_Server>
ACE_Protocol_Acceptor<ACE_Protocol_Server>::ACE_Protocol_Acceptor() : _handler_timeout(0)
{
}

template <class ACE_Protocol_Server>
int ACE_Protocol_Acceptor<ACE_Protocol_Server>::init(time_t handler_timeout)
{
    _handler_timeout = handler_timeout;
    return 0;
}

template <class ACE_Protocol_Server>
void ACE_Protocol_Acceptor<ACE_Protocol_Server>::release()
{
    ACE_Acceptor<ACE_Protocol_Server, ACE_SOCK_ACCEPTOR>::close();
}

template <class ACE_Protocol_Server>
int ACE_Protocol_Acceptor<ACE_Protocol_Server>::make_svc_handler (ACE_Protocol_Server *&sh)
{
    if(sh  == NULL)
    {
        ACE_NEW_RETURN(sh, ACE_Protocol_Server, -1);
    }

    sh->init(_handler_timeout);

    ACE_Reactor *r = this->reactor();
    sh->reactor( r );

    return 0;
}

template <class Handler>
class ACE_Protocol_Acceptor_Singleton : public ACE_Singleton<ACE_Protocol_Acceptor<Handler>, ACE_Thread_Mutex>
{};


#endif // ACE_ACCEPTOR_H
