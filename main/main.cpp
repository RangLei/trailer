#include <ace/ACE.h>
#include <ace/OS.h>

#include <ace/Log_Msg.h>

#include <ace/Get_Opt.h>
#include <ace/Configuration.h>
#include <ace/Configuration_Import_Export.h>

#include <ace/Assert.h>
#include <ace/Time_Value.h>

#include <mysql/mysql.h>

#include "cmd_down_from_db.h"

#include "server_msg_handler.h"
#include "protocol/ace_protocol_acceptor.h"
#include "database_mysql/database_sql.h"

int ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
    //default param
    ACE_TString     db_host             = ACE_TEXT("localhost") ;
    ACE_TString     db_user             = ACE_TEXT("root") ;
    ACE_TString     db_password         = ACE_TEXT("123456") ;
    ACE_TString     db_name             = ACE_TEXT("telitek") ;
    unsigned int    db_port             = 3306;
    unsigned int    is_create_db        = 0;
    unsigned int    is_create_table     = 0;
    unsigned int    db_polling_interval = 3;

    unsigned int    tcp_listen_port     = 20000;
    unsigned int    socket_timeout      = 1;

    unsigned int    is_daemon           = 0;

    //todo: use get_opt to handle argv

    //read param from ini
    {
        ACE_Configuration_Heap  ini;
        ACE_Ini_ImpExp          ini_import(ini);

        ACE_TCHAR               *ini_file = ACE_TEXT("trailer.ini");

        int rc = ini_import.import_config(ini_file);
        if(rc != 0)
        {
            ACE_DEBUG((LM_INFO, ACE_TEXT("ini import trailer.ini failed!\n use default param!\n")));
        }
        else
        {
            const ACE_Configuration_Section_Key &root_section = ini.root_section();
            ACE_Configuration_Section_Key db_section;
            int rc = ini.open_section(root_section, ACE_TEXT("database"), 0, db_section);

            if(rc != 0)  ACE_DEBUG((LM_INFO, ACE_TEXT("ini open_section [%s] error!\n"), ACE_TEXT("database")));
            else
            {
                ini.get_string_value(db_section, ACE_TEXT("db_host"), db_host);
                ini.get_string_value(db_section, ACE_TEXT("db_user"), db_user);
                ini.get_string_value(db_section, ACE_TEXT("db_password"), db_password);
                ini.get_string_value(db_section, ACE_TEXT("db_name"), db_name);
                ini.get_integer_value(db_section, ACE_TEXT("db_port"), db_port);
                ini.get_integer_value(db_section, ACE_TEXT("is_create_db"), is_create_db);
                ini.get_integer_value(db_section, ACE_TEXT("is_create_table"), is_create_table);
                ini.get_integer_value(db_section, ACE_TEXT("db_polling_interval"), db_polling_interval);
            }

            ACE_Configuration_Section_Key network_section;
            rc = ini.open_section(root_section, ACE_TEXT("network"), 0, network_section);
            if(rc != 0)  ACE_DEBUG((LM_INFO, ACE_TEXT("ini open_section [%s] error!\n"), ACE_TEXT("network")));
            else
            {
                ini.get_integer_value(network_section, ACE_TEXT("tcp_listen_port"), tcp_listen_port);
                ini.get_integer_value(network_section, ACE_TEXT("socket_timeout"), socket_timeout);
            }

            ACE_Configuration_Section_Key main_section;
            rc = ini.open_section(root_section, ACE_TEXT("main"), 0, main_section);
            if(rc != 0)  ACE_DEBUG((LM_INFO, ACE_TEXT("ini open_section [%s] error!\n"), ACE_TEXT("main")));
            else
            {
                ini.get_integer_value(main_section, ACE_TEXT("is_daemon"), is_daemon);
            }
        }
    }
    //todo: daemon
    if(is_daemon == 1)
    {
        ACE::daemonize();
    }

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

    if (!db_sql->init(db_host.c_str(), db_user.c_str(), db_password.c_str(), db_name.c_str(), db_port, NULL))
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s :database init fail\n"), __PRETTY_FUNCTION__));
        mysql_library_end(); return -1;
    }

    if(is_create_table)
    {
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
    }
#endif

    //AIO_Acceptor
    ACE_Protocol_Acceptor<Server_MSG_Handler> *acceptor =
            ACE_Protocol_Acceptor_Singleton<Server_MSG_Handler>::instance();


    rc = acceptor->init(socket_timeout);
    if(rc != 0)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : acceptpor init error!\n"), __PRETTY_FUNCTION__));
        mysql_library_end(); return -1;
    }

    ACE_INET_Addr local_addr(tcp_listen_port);
    rc = acceptor->open(local_addr);
    if(rc != 0)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : acceptpor open error!\n"), __PRETTY_FUNCTION__));
        mysql_library_end(); return -1;
    }

    ACE_DEBUG((LM_INFO, ACE_TEXT("%s : acceptpor open success!\n"), __PRETTY_FUNCTION__));

    Cmd_Down_From_DB *cmd_down_from_db = Cmd_Down_From_DB_Singleton::instance();

    ACE_ASSERT(cmd_down_from_db != NULL);

    ACE_Time_Value tv(db_polling_interval);
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

    delete  db_sql;
    db_sql = NULL;

    cmd_down_from_db->close();

    reactor->close();
    mysql_library_end();
    return 0;
}

