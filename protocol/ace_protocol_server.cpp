#include "ace_protocol_server.h"

#include <string.h>

#define MAX_RECV_SIZE (1024 * 1024)

ACE_Protocol_Server::ACE_Protocol_Server() : _time_out( 0 )
  , _timer_id(-1)
  , _msg_block_recv(NULL)
{}

int ACE_Protocol_Server::init(time_t timeout)
{
    _msg_block_recv = new ACE_Message_Block(MAX_RECV_SIZE);
    _time_out = timeout;
    return 0;
}

void ACE_Protocol_Server::release()
{
    if(_msg_block_recv != NULL)
    {
        _msg_block_recv->release();
        _msg_block_recv = NULL;
    }
}

int ACE_Protocol_Server::open (void *acceptor_or_connector)
{
    //heart time set
    ACE_Time_Value delay( 0 );
    if(_time_out > 0)
    {
        ACE_Time_Value interval( _time_out );
        _timer_id = reactor ()->schedule_timer( this, NULL, delay, interval );
        if ( _timer_id == -1 )
        {
            ACE_ERROR_RETURN ( ( LM_ERROR, ACE_TEXT( "schedule_timer set failure\n" ) ), -1 );
        }
    }

    if( reactor ()->register_handler(this,
                                     ACE_Event_Handler::READ_MASK) == -1)
    {
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%p\n"),
                           ACE_TEXT ("unable to register server handler")),
                          -1);
    }

    return 0;
}

int ACE_Protocol_Server::close(u_long flags)
{
    if ( _timer_id != -1 )
    {
        reactor ()->cancel_timer(_timer_id);
    }

    reactor ()->remove_handler(this, ACE_Event_Handler::ALL_EVENTS_MASK);

    peer().close();

    return 0;
}

int ACE_Protocol_Server::handle_input(ACE_HANDLE fd)
{
    //ACE_DEBUG ( ( LM_INFO, ACE_TEXT("into ACE_Protocol_Server::handle_input\n") ) );

    ACE_Time_Value time_out(_time_out);

    ssize_t rc = peer().recv( _msg_block_recv->rd_ptr()
                                , _msg_block_recv->size()
                                , &time_out );

    if ( rc <= 0 )
    {
        if ( rc == -1 && errno == ETIME )
        {
            ACE_DEBUG ( ( LM_INFO, ACE_TEXT("peer recv_n() time out\n") ) );
        }
        else if ( rc == -1 )
        {
            ACE_DEBUG ( ( LM_INFO, ACE_TEXT("peer recv_n() error\n") ) );
        }
        if ( rc == 0 )
        {
            ACE_DEBUG ( ( LM_INFO, ACE_TEXT("peer closed\n") ) );
        }

        return -1;
    }

    rc = handle_recv_message( _msg_block_recv->rd_ptr(), rc );

    return rc;

}

int ACE_Protocol_Server::handle_close(ACE_HANDLE fd, ACE_Reactor_Mask mask)
{
    ACE_DEBUG( (LM_INFO, ACE_TEXT("ACE_Protocol_Server::handle_close!\n")) );
    //stop
    close(0);
    release();

    delete this;
    return 0;
}

int ACE_Protocol_Server::handle_timeout(const ACE_Time_Value &time, const void *)
{
    return 0;
}

int ACE_Protocol_Server::handle_signal(int signum, siginfo_t * siginfo, ucontext_t *p)
{
    ACE_DEBUG( (LM_INFO, ACE_TEXT("ACE_Protocol_Server::handle_signal!\n")) );
    return 0;
}
