#ifndef AIO_CLIENT_HANDLER_H
#define AIO_CLIENT_HANDLER_H

#include <ace/Asynch_IO.h>
#include <ace/Message_Block.h>
#include <ace/INET_Addr.h>

#define MAX_RECV_BUFFER_SIZE (1024*1024)
class AIO_Client_Handler : public ACE_Service_Handler
{
public:
    int init(ACE_INET_Addr const &remote_addr, time_t timeout = 2);
    void release();

    void open (ACE_HANDLE new_handle, ACE_Message_Block &message_block);
    void close ();

    void handle_time_out (const ACE_Time_Value &tv,
                                    const void *act = 0);


    AIO_Client_Handler();

protected:
    void reconnect();

    ACE_Asynch_Read_Stream _read_stream;
    ACE_Asynch_Write_Stream _write_stream;

    ACE_INET_Addr _remote_addr;
    time_t  _timeout;
    long _time_id;

    ACE_Message_Block *_message_block;
};

#endif // AIO_CLIENT_HANDLER_H
