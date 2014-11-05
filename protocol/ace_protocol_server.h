#ifndef ACE_PROTOCOL_SERVER_H
#define ACE_PROTOCOL_SERVER_H

#include <ace/ACE.h>
#include <ace/SOCK_Stream.h>
#include <ace/Svc_Handler.h>

#define MAX_RECV_SIZE (1024 * 1024)

class ACE_Protocol_Server: public  ACE_Svc_Handler< ACE_SOCK_STREAM, ACE_NULL_SYNCH >
{
public:
    ACE_Protocol_Server();
    virtual int init(time_t timeout);
    virtual void release();

    virtual int open (void *acceptor_or_connector = 0);
    virtual int close(u_long flags);

    virtual int handle_input(ACE_HANDLE fd);
    virtual int handle_close(ACE_HANDLE fd, ACE_Reactor_Mask mask);
    virtual int handle_timeout(const ACE_Time_Value &time, const void *);
    virtual int handle_signal(int signum, siginfo_t *siginfo = 0, ucontext_t *p = 0);

    virtual int handle_recv_message(const char* buf, int length) = 0;
    virtual int handle_send_message(const char* buf, int length) = 0;

protected:
    time_t _time_out;
    long _timer_id;
    ACE_Message_Block *_msg_block_recv;

};



#endif // SERVER_H
