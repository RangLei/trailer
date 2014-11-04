#include "aio_server_handler.h"

#include <ace/OS.h>
#include <ace/Proactor.h>
#include <ace/SOCK.h>
#include <ace/Guard_T.h>

AIO_Server_Handler::AIO_Server_Handler() :
    _timeout(0)
  ,_time_id(0)
  ,_message_block_read(NULL)
  ,_message_block_write(NULL)
{
}

int AIO_Server_Handler::init(time_t timeout)
{
    _timeout = timeout;
    return 0;
}

void AIO_Server_Handler::release()
{
    if (_message_block_read != NULL)
    {
        _message_block_read->release();
        _message_block_read = NULL;
    }

    if (_message_block_write != NULL)
    {
        _message_block_write->release();
        _message_block_write = NULL;
    }
}

void AIO_Server_Handler::open (ACE_HANDLE new_handle,
                               ACE_Message_Block &message_block)
{
    if(_timeout > 0)
    {
        ACE_Time_Value time(0);
        ACE_Time_Value interval_time(_timeout);
        _time_id = this->proactor()->schedule_timer (*this,
                                                     NULL,
                                                     time,
                                                     interval_time);
        if (_time_id == -1)
        {
            ACE_DEBUG((LM_ERROR
                       ,ACE_TEXT("%s : schedule_timer failed\n")
                       ,__PRETTY_FUNCTION__));
            release();
            delete this;
            return;
        }
    }

    int rc = _read_stream.open(*this, new_handle);
    if(rc != 0)
    {
        ACE_DEBUG((LM_ERROR
                   ,ACE_TEXT("%s : _read_stream open failed\n")
                   ,__PRETTY_FUNCTION__));
    }

    if(rc == 0) rc = _write_stream.open(*this, new_handle);
    if(rc != 0)
    {
        ACE_DEBUG((LM_ERROR
                   ,ACE_TEXT("%s : _write_stream open failed\n")
                   ,__PRETTY_FUNCTION__));
    }

    if(rc != 0)
    {
        release();
        delete this;
    }
}

void AIO_Server_Handler::close ()
{
    if(_timeout > 0 &&  _time_id > 0)
    {
        this->proactor()->cancel_timer(_time_id);
    }

    _read_stream.cancel();
    _write_stream.cancel();

    ACE_HANDLE h = this->handle();
    ACE_OS::shutdown(h, SHUT_RDWR);
    ACE_OS::close(h);
}

void AIO_Server_Handler::addresses (const ACE_INET_Addr &remote_address,
                                    const ACE_INET_Addr &local_address)
{
    _remote_address = remote_address;
    _local_address = local_address;
}

void AIO_Server_Handler::handle_time_out (const ACE_Time_Value &tv,
                                          const void *act)
{
    ACE_DEBUG((LM_INFO, ACE_TEXT("%s : handle_timeout!\n")));
}

void AIO_Server_Handler::handle_write_stream (const ACE_Asynch_Write_Stream::Result &result)
{
    ACE_TRACE(__PRETTY_FUNCTION__);

    ACE_Guard<ACE_Recursive_Thread_Mutex> write_lock (_write_mutex);

    if( !result.success() )
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : error!"), __PRETTY_FUNCTION__));

        this->close();
        this->release();

        delete this;
    }

    ACE_Message_Block &msg  = result.message_block();

    if(msg.length() != 0)
    {
        _write_stream.write(msg, msg.length());
    }
    else
    {
        ACE_DEBUG((LM_INFO, ACE_TEXT("%s : success!"), __PRETTY_FUNCTION__));

        _message_block_write = msg.next();

        int rc = handle_write(&msg);
        if(rc != 0)
        {
            ACE_DEBUG((LM_INFO, ACE_TEXT("%s : handle_write return %d, delete this!"), __PRETTY_FUNCTION__, rc));

            this->close();
            this->release();

            delete this;
            return;
        }

        if(_message_block_write != NULL)
        {
            _write_stream.write(*_message_block_write, _message_block_write->length());
        }
    }


}

void AIO_Server_Handler::handle_read_stream (const ACE_Asynch_Read_Stream::Result &result)
{
    ACE_Guard<ACE_Recursive_Thread_Mutex> read_lock (_read_mutex);

    ACE_DEBUG((LM_INFO, ACE_TEXT("%s : 111111111111\n"), __PRETTY_FUNCTION__));
    if( !result.success() )
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("%s : error!"), __PRETTY_FUNCTION__));

        this->close();
        this->release();

        delete this;
    }

    ACE_Message_Block &msg  = result.message_block();

    _message_block_read = msg.next();

    int rc = handle_read(&msg);
    if(rc == -1)
    {
        ACE_DEBUG((LM_INFO, ACE_TEXT("%s : handle_read return %d, delete this!"), __PRETTY_FUNCTION__, rc));

        this->close();
        this->release();

        delete this;
    }

    if(rc > 0)
    {
        _message_block_read = &msg;
        _read_stream.read(*_message_block_read, _message_block_read->size() - _message_block_read->length());
    }
    else
    {
        if(_message_block_read != NULL)
        {
            _read_stream.read(*_message_block_read, _message_block_read->length());
        }
    }
}

int AIO_Server_Handler::handle_read(ACE_Message_Block *msg_block)
{
    msg_block->reset();
    //read(msg_block);
    return 0;
}

int AIO_Server_Handler::handle_write(ACE_Message_Block *msg_block)
{
    ACE_DEBUG((LM_INFO, ACE_TEXT("%s : 2222222222222\n"), __PRETTY_FUNCTION__));

    msg_block->release();
    return 0;
}

int AIO_Server_Handler::read(ACE_Message_Block *msg_block)
{
    ACE_Guard<ACE_Recursive_Thread_Mutex> read_lock (_read_mutex);

    if(_message_block_read == 0)
    {
        _message_block_read = msg_block;
        _read_stream.read(*msg_block, msg_block->size());
    }
    else
    {
        _message_block_read->cont(msg_block);
    }
    return 0;
}

int AIO_Server_Handler::write(ACE_Message_Block *msg_block)
{
    ACE_Guard<ACE_Recursive_Thread_Mutex> write_lock (_write_mutex);

    if(_message_block_write == NULL)
    {
        _message_block_write = msg_block;
        _write_stream.write(*_message_block_write, _message_block_write->length());
    }
    else
    {
        _message_block_write->cont(msg_block);
    }

    return 0;
}

