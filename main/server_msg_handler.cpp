#include <ace/Guard_T.h>

#include "server_msg_handler.h"
#include "database_mysql/database_sql.h"
#include "ip_handler_map.h"

Server_MSG_Handler::Server_MSG_Handler()
    : _db_sql(Database_SQL::instance())
    , _remote_ip(0)

{
}

int Server_MSG_Handler::open(void* acceptor_or_connector)
{
    int rc = Super::open(acceptor_or_connector);

    if(rc == 0)
    {
        ACE_INET_Addr remote_addr;

        this->peer().get_remote_addr(remote_addr);
        _remote_ip = remote_addr.get_ip_address();

        IP_Handler_Map *ip_handler_map =
                IP_Handler_Map_Singleton::instance();
        ACE_ASSERT(ip_handler_map != NULL);

        int rc = ip_handler_map->bind(_remote_ip, this->get_handle());
        if(rc == -1)
        {
            ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : ipo_handler_map->bind error!\n")
                       , __PRETTY_FUNCTION__));
            Super::close(0);
            return -1;
        }
    }
    return rc;
}

int Server_MSG_Handler::close(u_long flags)
{
    IP_Handler_Map *ip_handler_map =
            IP_Handler_Map_Singleton::instance();

    ACE_ASSERT(ip_handler_map != NULL);

    {
        int rc = ip_handler_map->unbind(_remote_ip);
        if(rc == -1)
        {
            ACE_DEBUG((LM_ERROR, ACE_TEXT("ip_handler_map->unbind(%d) error\n")
                   , _remote_ip));
        }
    }

    int rc = Super::close(flags);

    return  rc;
}

int Server_MSG_Handler::handle_recv_message(const char* buf, int length)
{
    if (_db_sql)
    {
        TRA_Download_Table_Data tra_table_data;

        ACE_INET_Addr remote_addr;
        peer().get_remote_addr(remote_addr);
        tra_table_data.ip = remote_addr.get_host_addr();

        tra_table_data.content = buf;
        tra_table_data.flag = 0;

        _db_sql->do_db_insert_table("tra_download", tra_table_data);
    }

    ACE_OS::fprintf(stdout, "%d--:%s\n", length, buf);

    ACE_OS::fflush(stdout);

    return 0;
}

int Server_MSG_Handler::handle_send_message(const char* buf, int length)
{
    ACE_Time_Value tv(_time_out);
    int rc = peer().send_n(buf, length, &tv);
    ACE_OS::fprintf(stdout, "send to client %d--:%s\n", rc, buf);

    return rc == length ? 0 : -1;
}
