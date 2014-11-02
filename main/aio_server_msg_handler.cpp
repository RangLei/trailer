#include <ace/Log_Msg.h>
#include <ace/OS.h>

#include "aio_server_msg_handler.h"
#include "msg_parse/server_msg_parse/server_msg_parse.h"
#include "database_mysql/database_sql.h"

AIO_Server_Msg_Handler::AIO_Server_Msg_Handler()
    : _db_sql(Database_SQL::instance())
{
}

AIO_Server_Msg_Handler::~AIO_Server_Msg_Handler()
{
    _db_sql = NULL;
}

void AIO_Server_Msg_Handler::open (ACE_HANDLE new_handle, ACE_Message_Block &message_block)
{
    Super::open(new_handle, message_block);

    ACE_Message_Block *msg_recv = new ACE_Message_Block(MAX_RECV_BUFFER_SIZE);

    read(msg_recv);

    ACE_DEBUG((LM_INFO, ACE_TEXT("%s : 00000000000\n"), __PRETTY_FUNCTION__));
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
