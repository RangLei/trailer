#include <ace/ACE.h>
#include <ace/Log_Msg.h>
#include <ace/Get_Opt.h>
#include <ace/OS.h>

#include <ace/Proactor.h>

#include "aio_handler/aio_handler.h"
#include "aio_server_msg_handler.h"
int ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
    //todo: use get_opt to handle argv

    //todo: daemon

    //AIO_Acceptor
    AIO_Acceptor<AIO_Server_Msg_Handler> *acceptor = AIO_Acceptor_Singleton<AIO_Server_Msg_Handler>::instance();

    ACE_INET_Addr local_addr(8000);
    int rc = acceptor->open(local_addr);
    if(rc != 0)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : acceptpor open error!\n"), __PRETTY_FUNCTION__));
        return -1;
    }

    ACE_DEBUG((LM_INFO, ACE_TEXT("%s : acceptpor open success!\n"), __PRETTY_FUNCTION__));

    ACE_Proactor *proactor = ACE_Proactor::instance();

    //while(!proactor->event_loop_done())
    {
        proactor->run_event_loop();
    }

    return 0;
}

