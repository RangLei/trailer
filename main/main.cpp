#include <ace/ACE.h>
#include <ace/Log_Msg.h>
#include <ace/Get_Opt.h>
#include <ace/OS.h>

#include <ace/Proactor.h>

#include "aio_handler/aio_handler.h"
#include "aio_server_msg_handler.h"
#include "database_mysql/database_sql.h"

int ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
    //todo: use get_opt to handle argv

    //todo: daemon

    //todo: db
    Database_SQL *db_sql = new Database_SQL;
    if (NULL == db_sql)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s :new Database_SQL fail\n"), __PRETTY_FUNCTION__));
        return -1;
    }
    if (!db_sql->init("localhost", "root", "123456", "telitek", 3306, NULL))
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s :database init fail\n"), __PRETTY_FUNCTION__));
        return -1;
    }

    //AIO_Acceptor
    AIO_Acceptor<AIO_Server_Msg_Handler> *acceptor = AIO_Acceptor_Singleton<AIO_Server_Msg_Handler>::instance();


    int rc = acceptor->init(db_sql, 2);
    if(rc != 0)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : acceptpor init error!\n"), __PRETTY_FUNCTION__));
        return -1;
    }

    ACE_INET_Addr local_addr(8000);
    rc = acceptor->open(local_addr, 0, true,
                        ACE_DEFAULT_ASYNCH_BACKLOG, 1,
                        ACE_Proactor::instance());
    if(rc != 0)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : acceptpor open error!\n"), __PRETTY_FUNCTION__));
        return -1;
    }

    ACE_DEBUG((LM_INFO, ACE_TEXT("%s : acceptpor open success!\n"), __PRETTY_FUNCTION__));

    ACE_Proactor *proactor = ACE_Proactor::instance();

    while(!proactor->event_loop_done())
    {
        proactor->run_event_loop();
    }

    delete  db_sql;
    db_sql = NULL;
    return 0;
}

