#ifndef AIO_ACCEPTOR_H
#define AIO_ACCEPTOR_H

#include <ace/Asynch_Acceptor.h>
#include <ace/Log_Msg.h>
#include <ace/Singleton.h>
#include <ace/Thread_Mutex.h>

template <class HANDLER>
class AIO_Acceptor : public ACE_Asynch_Acceptor<HANDLER>
{
public:
    AIO_Acceptor(void);
    int init(time_t timeout = 2);

    HANDLER *make_handler (void);
private:
    time_t _heart_time;
};

template <class HANDLER>
AIO_Acceptor<HANDLER>::AIO_Acceptor(void) : _heart_time(0)
{
}

template <class HANDLER>
int AIO_Acceptor<HANDLER>::init(time_t timeout)
{
    _heart_time = timeout;
    return 0;
}

template <class HANDLER>
HANDLER * AIO_Acceptor<HANDLER>::make_handler (void)
{
    HANDLER * handler = new HANDLER;
    if (handler == NULL)
    {
        ACE_DEBUG ((LM_ERROR, ACE_TEXT("%s: new new HANDLER failed\n")
                    ,__PRETTY_FUNCTION__));
        return NULL;
    }
    handler->init(_heart_time);
    return handler;
}

template <class HANDLER>
class AIO_Acceptor_Singleton : public ACE_Singleton<AIO_Acceptor<HANDLER>, ACE_Thread_Mutex>
{};
#endif // AIO_ACCEPTOR_H
