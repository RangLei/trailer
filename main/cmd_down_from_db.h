#ifndef CMD_DOWN_FROM_DB_H
#define CMD_DOWN_FROM_DB_H

#include <ace/Asynch_IO.h>
#include <ace/Time_Value.h>

#include <ace/Singleton.h>
#include <ace/Thread_Mutex.h>

#include "ip_aio_handler_map.h"

class Cmd_Down_From_DB : public ACE_Handler
{
public:
    Cmd_Down_From_DB();

    int open(ACE_Time_Value const &interval);
    void close();

    virtual void handle_time_out (const ACE_Time_Value &tv,
                                  const void *act = 0);
private:
    long timer_id;
    IP_AIO_Handler_Map *ip_aio_handler_map;
};

typedef ACE_Singleton<Cmd_Down_From_DB, ACE_Thread_Mutex> Cmd_Down_From_DB_Singleton;
#endif // CMD_DOWN_FROM_DB_H