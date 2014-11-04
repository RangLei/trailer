#include <ace/Log_Msg.h>
#include <ace/OS.h>
#include <ace/Assert.h>
#include <ace/Reactor.h>

#include "aio_server_msg_handler.h"
#include "msg_parse/server_msg_parse/server_msg_parse.h"
#include "database_mysql/database_sql.h"
#include "ip_aio_handler_map.h"

AIO_Server_Msg_Handler::AIO_Server_Msg_Handler()
    : _db_sql(Database_SQL::instance())
    , msg_recv(NULL)
{
    msg_recv = new ACE_Message_Block(MAX_RECV_BUFFER_SIZE);
}

AIO_Server_Msg_Handler::~AIO_Server_Msg_Handler()
{
    _db_sql = NULL;
    if(msg_recv != NULL)
    {
        msg_recv->release();
    }
}

void AIO_Server_Msg_Handler::open (ACE_HANDLE new_handle, ACE_Message_Block &message_block)
{
    Super::open(new_handle, message_block);

    ACE_UINT32 ip= this->_remote_address.get_ip_address();

    IP_AIO_Handler_Map *ip_aio_handler_map =
            IP_AIO_Handler_Map_Singleton::instance();
    ACE_ASSERT(ip_aio_handler_map != NULL);

    int rc = ip_aio_handler_map->bind(ip, this);
    if(rc == -1)
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : ip_aio_handler_map->bind error!\n")
                   , __PRETTY_FUNCTION__));
        Super::close();
        return;
    }

    ACE_Reactor::instance()->register_handler(new_handle,
                                              this,
                                              ACE_Event_Handler::READ_MASK);

    ACE_DEBUG((LM_INFO, ACE_TEXT("%s : 00000000000\n"), __PRETTY_FUNCTION__));
}

void AIO_Server_Msg_Handler::close ()
{
    ACE_Reactor::instance()->remove_handler(this->handle(), ACE_Event_Handler::READ_MASK);
    Super::close();

    ACE_UINT32 ip= this->_remote_address.get_ip_address();

    IP_AIO_Handler_Map *ip_aio_handler_map =
            IP_AIO_Handler_Map_Singleton::instance();

    ACE_ASSERT(ip_aio_handler_map != NULL);

    ip_aio_handler_map->unbind(ip);
}

int AIO_Server_Msg_Handler::handle_input (ACE_HANDLE fd)
{
    read(msg_recv);
    return 0;
}

int AIO_Server_Msg_Handler::handle_read(ACE_Message_Block *msg_block)
{
    //todo:
    //...
    //TRA_Download_Table_Data tra_table_data;
    //tra_table_data.ip = xxx;
    //.
    //.
    //.
    //_db_sql->do_db_insert_table("tra_download", tra_table_data);

    ACE_OS::fprintf(stdout, "%d--:%s\n", msg_block->length(),
                    msg_block->rd_ptr());

    ACE_OS::fflush(stdout);

    bool continue_recv = false;
    if(continue_recv)
    {
        return 1;
    }
    else
    {
        return Super::handle_read(msg_block);
    }
}

int AIO_Server_Msg_Handler::handle_write(ACE_Message_Block *msg_block)
{
    //todo:
//    std::list<TRA_Download_Table_Data> tra_table_datas;
//    _db_sql->do_db_select_table("tra_download", tra_table_datas);
//    _db_sql->do_db_update_table("tra_download", tra_table_datas);

    msg_block->release();
    return 0;
}
