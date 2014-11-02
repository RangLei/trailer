#ifndef AIO_SERVER_MSG_HANDLER_H
#define AIO_SERVER_MSG_HANDLER_H

#include "aio_handler/aio_server_handler.h"

class Database_SQL;
class AIO_Server_Msg_Handler : public AIO_Server_Handler
{
    typedef AIO_Server_Handler Super;
public:
    AIO_Server_Msg_Handler();
    ~AIO_Server_Msg_Handler();

    virtual void open (ACE_HANDLE new_handle, ACE_Message_Block &message_block);
    virtual int handle_read(ACE_Message_Block *msg_block);
    virtual int handle_write(ACE_Message_Block *msg_block);

private:
    Database_SQL *_db_sql;

};
#endif // AIO_SERVER_MSG_HANDLER_H
