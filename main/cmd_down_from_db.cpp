#include "cmd_down_from_db.h"

#include <ace/OS.h>
#include <ace/Log_Msg.h>
#include <ace/Reactor.h>

#include "database_mysql/database_sql.h"

Cmd_Down_From_DB::Cmd_Down_From_DB() :
    timer_id(-1)
  , ip_handler_map(NULL)
  , _db_sql(Database_SQL::instance())
{
}

int Cmd_Down_From_DB::open(ACE_Time_Value const &interval)
{
    ip_handler_map = IP_Handler_Map_Singleton::instance();

    if(ip_handler_map == NULL)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : ip_handler_map == NULL error!\n")));
        return -1;
    }

    ACE_Time_Value now(0);// = ACE_OS::gettimeofday();

    timer_id = ACE_Reactor::instance()->schedule_timer(this, NULL, now, interval);
    if(timer_id == -1)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : reactor->schedule_timer error!\n")));
        return -1;
    }

    return 0;
}

void Cmd_Down_From_DB::close()
{
    if(timer_id != NULL)
    {
        ACE_Reactor::instance()->cancel_timer(timer_id);
    }
}

int Cmd_Down_From_DB::handle_timeout (const ACE_Time_Value &tv,
                                      const void *act)
{
    ACE_DEBUG((LM_INFO, ACE_TEXT("%s : 111111111\n"), __PRETTY_FUNCTION__));

    if(ip_handler_map == NULL)
    {
        ACE_DEBUG((LM_INFO, ACE_TEXT("%s : ip_handler_map == NULL error!\n"), __PRETTY_FUNCTION__));
        return 0;
    }

    // from database telitek abd table tra_download
    std::list<TRA_Download_Table_Data> tra_table_datas;
    if (_db_sql)
    {
        _db_sql->do_db_select_table("tra_download", tra_table_datas);
    }

    std::list<TRA_Download_Table_Data>::iterator iter;
    for ( iter = tra_table_datas.begin(); iter != tra_table_datas.end(); ++iter)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("content:%s !\n"),iter->content.c_str()));

        unsigned long ip = ACE_OS::inet_addr(iter->ip.c_str());
        ip = ACE_NTOHL(ip);

        int fd = -1;

        int rc = 0;
        rc = ip_handler_map->find(ip, fd);
        if( rc == -1 )//not find
        {
            ACE_DEBUG((LM_ERROR, ACE_TEXT("IP = %s : fd = %d not find\n")
                       , iter->ip.c_str()
                       , fd));
        }
        else
        {
            ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s : 001\n"), __PRETTY_FUNCTION__));
            const ACE_TCHAR *msg = iter->content.c_str();

            rc = ACE_OS::send(fd, msg, ACE_OS::strlen(msg));
            if (rc != ACE_OS::strlen(msg))
            {
                ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : rc = %d send error\n")
                           , __PRETTY_FUNCTION__
                           , rc));

            }
            //ACE_DEBUG((LM_INFO, ACE_TEXT("33333333333333333:%s\n"),msg_block->rd_ptr()));
            iter->flag = 1;
            _db_sql->do_db_update_table("tra_download", *iter);
        }
    }

    return 0;
}
