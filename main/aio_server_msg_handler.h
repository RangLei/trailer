#ifndef AIO_SERVER_MSG_HANDLER_H
#define AIO_SERVER_MSG_HANDLER_H

#include "aio_handler/aio_server_handler.h"

class AIO_Server_Msg_Handler : public AIO_Server_Handler
{
    typedef AIO_Server_Handler Super;
public:
    virtual void open (ACE_HANDLE new_handle, ACE_Message_Block &message_block);
    virtual int handle_read(ACE_Message_Block *msg_block);
    virtual int handle_write(ACE_Message_Block *msg_block);

private:

};
#endif // AIO_SERVER_MSG_HANDLER_H
