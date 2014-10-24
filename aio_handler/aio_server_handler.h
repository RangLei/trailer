#ifndef AIO_SERVER_HANDLER_H
#define AIO_SERVER_HANDLER_H
#include <ace/Asynch_IO.h>
#include <ace/Message_Block.h>

#define MAX_RECV_BUFFER_SIZE (1024*1024)

class AIO_Server_Handler : public ACE_Service_Handler
{
public:
    AIO_Server_Handler();

    virtual int init(time_t timeout = 2);
    virtual void release();

    /**
     * @brief open
     * @param new_handle
     * @param message_block
     */
    virtual void open (ACE_HANDLE new_handle,
               ACE_Message_Block &message_block);

    /**
     * @brief close
     */
    virtual void close ();

    virtual int read(ACE_Message_Block *msg_block);
    virtual int write(ACE_Message_Block *msg_block);

protected:
    /**
     * @brief handle_read
     * callback by handle_write_stream, this is an callback interface for users
     * to handle msg that had readed
     * @param msg_block
     * born from read(), dead to handle_read();
     * @return
     * -1  : io/socket error! unregister this from proactor and delete this
     * 0   : perfect recv! recv's lenth equal msg_block's size, or this msg not
     * need recv any bytes, and may perfect handle as read()'s expect
     * >0  : return wish to continue recv's length, recv's action had finished,
     * but the recv's lenth is less than read()'s expect, so continue recv
     */
    virtual int handle_read(ACE_Message_Block *msg_block);
    virtual int handle_write(ACE_Message_Block *msg_block);

    virtual void handle_time_out (const ACE_Time_Value &tv, const void *act = 0);
    virtual void handle_write_stream (const ACE_Asynch_Write_Stream::Result &result);
    virtual void handle_read_stream (const ACE_Asynch_Read_Stream::Result &result);

    ACE_Asynch_Read_Stream _read_stream;
    ACE_Asynch_Write_Stream _write_stream;

    time_t _timeout;
    long _time_id;

    ACE_Message_Block *_message_block_read;
    ACE_Message_Block *_message_block_write;
};

#endif // AIO_SERVER_HANDLER_H
