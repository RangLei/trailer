#include <ace/ACE.h>
#include <ace/Log_Msg.h>
#include <ace/Get_Opt.h>
#include <ace/OS.h>
#include <ace/Assert.h>
#include <ace/Proactor.h>
#include <ace/Time_Value.h>
#include <ace/Asynch_Pseudo_Task.h>
#include "aio_handler/aio_handler.h"
#include "aio_server_msg_handler.h"
#include "cmd_down_from_db.h"
#include "reactor_task.h"

#include "database_mysql/database_sql.h"

int ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
    //todo: use get_opt to handle argv

    //todo: daemon

    //todo: db

#if 1
    Database_SQL *db_sql = Database_SQL::instance();
    if (NULL == db_sql)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s :Database_SQL::instance() fail\n"), __PRETTY_FUNCTION__));
        return -1;
    }
    if (!db_sql->init("localhost", "root", "123456", "telitek", 3306, NULL))
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s :database init fail\n"), __PRETTY_FUNCTION__));
        return -1;
    }

    char *creat_table = "CREATE TABLE IF NOT EXISTS `tra_download` ("
                        "`id` int(11) NOT NULL AUTO_INCREMENT,"
                        "`created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,"
                        "`ip` varchar(16) COLLATE utf8_unicode_ci NOT NULL,"
                        "`content` varchar(255) COLLATE utf8_unicode_ci NOT NULL,"
                        "`flag` tinyint(4) NOT NULL DEFAULT '0',"
                        "PRIMARY KEY (`id`)"
                        ") ENGINE=InnoDB DEFAULT CHARSET=utf8";
    if (db_sql->do_db_real_query(creat_table, strlen(creat_table)))
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s :database creat tra_download table fail\n"), __PRETTY_FUNCTION__));
        return -1;
    }
#endif
    //reactor
    Reactor_Task *reactor_task = Reactor_Task_Singleton::instance();
    reactor_task->open();

    //AIO_Acceptor
    AIO_Acceptor<AIO_Server_Msg_Handler> *acceptor = AIO_Acceptor_Singleton<AIO_Server_Msg_Handler>::instance();


    int rc = acceptor->init(0);
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

    Cmd_Down_From_DB *cmd_down_from_db = Cmd_Down_From_DB_Singleton::instance();

    ACE_ASSERT(cmd_down_from_db != NULL);

    ACE_Time_Value tv(3);
    rc = cmd_down_from_db->open(tv);
    if(rc != 0)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("cmd_down_from_db->open error!\n")));
        return -1;
    }


    ACE_Proactor *proactor = ACE_Proactor::instance();

    while(!proactor->event_loop_done())
    {
        proactor->run_event_loop();
    }

    //delete  db_sql;
    //db_sql = NULL;

    cmd_down_from_db->close();

    reactor_task->close();

    return 0;
}

