#ifndef AIO_SERVER_HANDLER_H
#define AIO_SERVER_HANDLER_H
#include <ace/Asynch_IO.h>
#include <ace/Message_Block.h>

#define MAX_RECV_BUFFER_SIZE (1024*1024)

class AIO_Server_Handler : public ACE_Service_Handler
{
public:
    AIO_Server_Handler();
    int init(time_t timeout = 2);

    void release();
    void open (ACE_HANDLE new_handle,
                         ACE_Message_Block &message_block);
    void close ();

    void handle_time_out (const ACE_Time_Value &tv,
                                    const void *act = 0);

protected:

    ACE_Asynch_Read_Stream _read_stream;
    ACE_Asynch_Write_Stream _write_stream;

    time_t _timeout;
    long _time_id;

    ACE_Message_Block *_message_block;

};

#endif // AIO_SERVER_HANDLER_H
