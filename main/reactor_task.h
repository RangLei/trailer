#ifndef REACTOR_TASK_H
#define REACTOR_TASK_H

#include <ace/Task.h>
#include <ace/Thread_Mutex.h>
#include <ace/Singleton.h>

class Reactor_Task : public ACE_Task<ACE_MT_SYNCH>
{
public:
    Reactor_Task();
    int open();
    void close();
    virtual int svc (void);
};

typedef ACE_Singleton<Reactor_Task, ACE_Thread_Mutex> Reactor_Task_Singleton;

#endif // REACTOR_TASK_H
