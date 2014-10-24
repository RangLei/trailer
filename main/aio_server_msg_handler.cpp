#include <ace/Log_Msg.h>

#include "aio_server_msg_handler.h"
#include "msg_parse/server_msg_parse/server_msg_parse.h"

#include <ace/OS.h>
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
     ACE_OS::fprintf(stdout, "--:%s\n", msg_block->rd_ptr());
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

     msg_block->release();
     return 0;
 }
