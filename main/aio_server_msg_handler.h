#ifndef AIO_SERVER_MSG_HANDLER_H
#define AIO_SERVER_MSG_HANDLER_H

#include <ace/Event_Handler.h>
#include "aio_handler/aio_server_handler.h"

class Database_SQL;
class AIO_Server_Msg_Handler : public AIO_Server_Handler
        , public ACE_Event_Handler
{
    typedef AIO_Server_Handler Super;
public:
    AIO_Server_Msg_Handler();
    ~AIO_Server_Msg_Handler();

    virtual void open (ACE_HANDLE new_handle, ACE_Message_Block &message_block);
    virtual void close ();
    virtual int handle_read(ACE_Message_Block *msg_block);
    virtual int handle_write(ACE_Message_Block *msg_block);

    virtual int handle_input (ACE_HANDLE fd = ACE_INVALID_HANDLE);

private:
    Database_SQL *_db_sql;
    ACE_Message_Block *msg_recv;

};
#endif // AIO_SERVER_MSG_HANDLER_H
