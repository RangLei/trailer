#ifndef AIO_CONNECTOR_H
#define AIO_CONNECTOR_H

#include <ace/Asynch_Connector.h>
#include <ace/INET_Addr.h>
#include <ace/Time_Value.h>
#include <ace/Log_Msg.h>
#include <ace/Singleton.h>
#include <ace/Thread_Mutex.h>

template <class HANDLER>
class AIO_Connector : public ACE_Asynch_Connector<HANDLER>
{
public:
    AIO_Connector();
    ~AIO_Connector();

    int init(ACE_INET_Addr const &remote_addr, time_t timeout = 2);
    void close();

    void handle_connect (const ACE_Asynch_Connect::Result &result);
    HANDLER* make_handler (void);

private:
    ACE_INET_Addr _remote_addr;
    time_t _timeout;
    bool _has_connect;
};

template <class HANDLER>
AIO_Connector<HANDLER>::AIO_Connector()
    : _has_connect(false)
{
}

template <class HANDLER>
AIO_Connector<HANDLER>::~AIO_Connector()
{
}

template <class HANDLER>
int AIO_Connector<HANDLER>::init(ACE_INET_Addr const &remote_addr, time_t timeout)
{
    _remote_addr = remote_addr;

    _timeout = timeout;

    return 0;
}

template <class HANDLER>
void AIO_Connector<HANDLER>::close()
{
    this->cancel();
}

template <class HANDLER>
void AIO_Connector<HANDLER>::handle_connect (const ACE_Asynch_Connect::Result &result)
{
    ACE_Asynch_Connector<HANDLER>::handle_connect(result);

    if (!result.success () ||
        result.connect_handle () == ACE_INVALID_HANDLE)
    {
        //ACE_DEBUG...
        ACE_OS::sleep(1);
        this->connect(_remote_addr);
    }
    else
    {
        _has_connect = true;
    }
}

template <class HANDLER>
HANDLER* AIO_Connector<HANDLER>::make_handler (void)
{
    HANDLER *handler = new HANDLER;
    if(handler == NULL)
    {
        ACE_DEBUG((LM_ERROR
                   ,ACE_TEXT("%s : new HANDLER failed\n")
                   ,__PRETTY_FUNCTION__));
        return NULL;
    }

    handler->init(_remote_addr, _timeout);
    return handler;
}

template <class HANDLER>
class AIO_Connector_Singleton : public ACE_Singleton<AIO_Connector<HANDLER>, ACE_Thread_Mutex>
{};

#endif // AIO_CONNECTOR_H
