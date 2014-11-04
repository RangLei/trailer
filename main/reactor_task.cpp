#include "reactor_task.h"

#include <ace/Reactor.h>
Reactor_Task::Reactor_Task()
{
}

int Reactor_Task::open()
{
    activate();

    return 0;
}

void Reactor_Task::close()
{
    ACE_Reactor::instance()->end_reactor_event_loop();
}

int Reactor_Task::svc (void)
{
    while(!ACE_Reactor::instance()->event_loop_done())
    {
        ACE_Reactor::instance()->run_reactor_event_loop();
    }
}
