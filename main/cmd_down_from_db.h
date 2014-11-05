#ifndef CMD_DOWN_FROM_DB_H
#define CMD_DOWN_FROM_DB_H

#include <ace/Asynch_IO.h>
#include <ace/Time_Value.h>

#include <ace/Singleton.h>
#include <ace/Thread_Mutex.h>
#include <ace/Event_Handler.h>

#include "ip_handler_map.h"

class Database_SQL;
class Cmd_Down_From_DB : public ACE_Event_Handler
{
public:
    Cmd_Down_From_DB();

    int open(ACE_Time_Value const &interval);
    void close();

    virtual int handle_timeout (const ACE_Time_Value &tv,
                                const void *act = 0);
private:
    long timer_id;
    IP_Handler_Map *ip_handler_map;
    Database_SQL *_db_sql;
};

typedef ACE_Singleton<Cmd_Down_From_DB, ACE_Thread_Mutex> Cmd_Down_From_DB_Singleton;
#endif // CMD_DOWN_FROM_DB_H
