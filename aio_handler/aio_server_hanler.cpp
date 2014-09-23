#include "aio_server_handler.h"

#include <ace/OS.h>
#include <ace/Proactor.h>
#include <ace/SOCK.h>

AIO_Server_Handler::AIO_Server_Handler() :
    _timeout(0)
  ,_time_id(0)
  ,_message_block(NULL)
{
}

int AIO_Server_Handler::init(time_t timeout)
{
    _timeout = timeout;
    if (_message_block == NULL)
        _message_block = new ACE_Message_Block (MAX_RECV_BUFFER_SIZE);

    return 0;
}

void AIO_Server_Handler::release()
{
    if (_message_block != NULL)
    {
        _message_block->release();
        delete _message_block;
        _message_block = NULL;
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
    else
    {
        _read_stream.read(*_message_block, MAX_RECV_BUFFER_SIZE);
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

void AIO_Server_Handler::handle_time_out (const ACE_Time_Value &tv,
                                          const void *act)
{

}

