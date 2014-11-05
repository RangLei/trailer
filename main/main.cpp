#include <ace/ACE.h>
#include <ace/Log_Msg.h>
#include <ace/Get_Opt.h>
#include <ace/OS.h>
#include <ace/Assert.h>
#include <ace/Time_Value.h>

#include <mysql/mysql.h>

#include "cmd_down_from_db.h"

#include "server_msg_handler.h"
#include "protocol/ace_protocol_acceptor.h"
#include "database_mysql/database_sql.h"

int ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
    //todo: use get_opt to handle argv

    //todo: daemon

    //todo: db

#if 1
    int rc = mysql_library_init(0, NULL, NULL);
    if(rc != 0)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s :mysql_library_init fail\n"), __PRETTY_FUNCTION__));
        return -1;
    }

    Database_SQL *db_sql = Database_SQL::instance();
    if (NULL == db_sql)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s :Database_SQL::instance() fail\n"), __PRETTY_FUNCTION__));
        mysql_library_end(); return -1;
    }
    if (!db_sql->init("localhost", "root", "123456", "telitek", 3306, NULL))
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s :database init fail\n"), __PRETTY_FUNCTION__));
        mysql_library_end(); return -1;
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
        mysql_library_end(); return -1;
    }
#endif
    //AIO_Acceptor
    ACE_Protocol_Acceptor<Server_MSG_Handler> *acceptor =
            ACE_Protocol_Acceptor_Singleton<Server_MSG_Handler>::instance();


    rc = acceptor->init(1);
    if(rc != 0)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : acceptpor init error!\n"), __PRETTY_FUNCTION__));
        mysql_library_end(); return -1;
    }

    ACE_INET_Addr local_addr(8000);
    rc = acceptor->open(local_addr);
    if(rc != 0)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : acceptpor open error!\n"), __PRETTY_FUNCTION__));
        mysql_library_end(); return -1;
    }

    ACE_DEBUG((LM_INFO, ACE_TEXT("%s : acceptpor open success!\n"), __PRETTY_FUNCTION__));

    Cmd_Down_From_DB *cmd_down_from_db = Cmd_Down_From_DB_Singleton::instance();

    ACE_ASSERT(cmd_down_from_db != NULL);

    ACE_Time_Value tv(3);
    rc = cmd_down_from_db->open(tv);
    if(rc != 0)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("cmd_down_from_db->open error!\n")));
        mysql_library_end(); return -1;
    }


    ACE_Reactor *reactor = ACE_Reactor::instance();

    while(!reactor->reactor_event_loop_done())
    {
        reactor->run_reactor_event_loop();
    }

    //delete  db_sql;
    //db_sql = NULL;

    cmd_down_from_db->close();

    reactor->close();
    mysql_library_end();
    return 0;
}

