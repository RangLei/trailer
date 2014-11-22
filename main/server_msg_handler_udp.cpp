#include <ace/Reactor.h>
#include <ace/Log_Msg.h>

#include "server_msg_handler_udp.h"

#include "database_mysql/database_sql.h"

#define MAX_RECV_SIZE (1024 * 1024)

Server_Msg_Handler_UDP::Server_Msg_Handler_UDP()
    : _msg_block_recv(NULL)
    , _db_sql(Database_SQL::instance())
{
}

int Server_Msg_Handler_UDP::init(int port, ACE_TCHAR* ip)
{
    _local_addr.set(port, ip);
    _msg_block_recv = new ACE_Message_Block(MAX_RECV_SIZE);
    return 0;
}

void Server_Msg_Handler_UDP::release()
{
    if(_msg_block_recv != NULL)
    {
        _msg_block_recv->release();
        _msg_block_recv = NULL;
    }
}

int Server_Msg_Handler_UDP::open()
{
    int rc = _sock_dgram.open(_local_addr);
    if(rc != 0)
    {
        ACE_TCHAR addr_str[128];
        _local_addr.addr_to_string(addr_str, sizeof(addr_str));
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : _sock_dgram.open (%s) error!")
                   , __PRETTY_FUNCTION__
                   , addr_str));
        return -1;
    }

    //this->set_handle(_sock_dgram.get_handle());

    rc = ACE_Reactor::instance()->register_handler(_sock_dgram.get_handle(), this, ACE_Event_Handler::READ_MASK);
    if(rc != 0)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : ACE_Reactor::register_handler error!")
                   , __PRETTY_FUNCTION__));
        _sock_dgram.close();
        return -1;
    }

    return 0;
}

void Server_Msg_Handler_UDP::close()
{
    ACE_Reactor::instance()->remove_handler(_sock_dgram.get_handle(), ACE_Event_Handler::ALL_EVENTS_MASK);
    _sock_dgram.close();
}

int Server_Msg_Handler_UDP::handle_input(ACE_HANDLE fd)
{
    ACE_INET_Addr remote_addr;
    char *ptr = _msg_block_recv->rd_ptr();
    int size = _msg_block_recv->size();

    ssize_t rc = _sock_dgram.recv(ptr, size, remote_addr);


    if(rc > 0)
    {
        char *buf = _msg_block_recv->rd_ptr();
        int length = rc;

        buf[length] = '\0';

        if (_db_sql)
        {
            TRA_Table_Data tra_table_data;
            ACE_TCHAR addr_str [128];
            remote_addr.addr_to_string(addr_str, sizeof(addr_str));
            tra_table_data.ip = addr_str;
            tra_table_data.content = buf;
            tra_table_data.flag = 0;

            _db_sql->do_db_insert_table("tra_upload", tra_table_data);
        }

        ACE_OS::fprintf(stdout, "%d--:%s\n", length, buf);

        ACE_OS::fflush(stdout);

    }
    else
    {
        return -1;
    }

    return 0;
}

int Server_Msg_Handler_UDP::handle_close(ACE_HANDLE fd, ACE_Reactor_Mask mask)
{
    //reopen
    close();
    open();

    return 0;
}

int Server_Msg_Handler_UDP::send_message(const ACE_INET_Addr& remote_addr
                                         , ACE_TCHAR const* msg, int msg_len)
{
    int rc = _sock_dgram.send(msg, msg_len, remote_addr);

    return rc;
}
