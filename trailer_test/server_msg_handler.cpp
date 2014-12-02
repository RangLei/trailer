#include <ace/Guard_T.h>

#include "server_msg_handler.h"
#include "database_mysql/database_sql.h"
#include "addr_handler_map.h"

Server_MSG_Handler::Server_MSG_Handler()
    : _db_sql(Database_SQL::instance())
{
}

int Server_MSG_Handler::open(void* acceptor_or_connector)
{
    int rc = Super::open(acceptor_or_connector);

    if(rc == 0)
    {
        this->peer().get_remote_addr(_remote_addr);

        Addr_Handler_Map *addr_handler_map =
                Addr_Handler_Map_Singleton::instance();
        ACE_ASSERT(addr_handler_map != NULL);

        int rc = addr_handler_map->bind(_remote_addr, this->get_handle());
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
    Addr_Handler_Map *addr_handler_map =
            Addr_Handler_Map_Singleton::instance();

    ACE_ASSERT(addr_handler_map != NULL);

    {
        int rc = addr_handler_map->unbind(_remote_addr);
        if(rc == -1)
        {
            ACE_TCHAR addr_str [128];
            _remote_addr.addr_to_string(addr_str, sizeof(addr_str));
            ACE_DEBUG((LM_ERROR, ACE_TEXT("addr_handler_map->unbind(%s) error\n"), addr_str));
        }
    }

    int rc = Super::close(flags);

    return  rc;
}

int Server_MSG_Handler::handle_recv_message(const char* buf, int length)
{
    if (_db_sql)
    {
        TRA_Table_Data tra_table_data;
        ACE_TCHAR addr_str [128];
        _remote_addr.addr_to_string(addr_str, sizeof(addr_str));
        tra_table_data.ip = addr_str;
        tra_table_data.content = buf;
        tra_table_data.flag = 0;

        _db_sql->do_db_insert_table("tra_upload", tra_table_data);
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
