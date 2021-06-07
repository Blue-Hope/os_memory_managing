#ifndef RUN_QUEUE
#define RUN_QUEUE

#include "queue.h"
// #include "process.h"

class RunQueue : public Queue<string>
{
public:
    int priority;
    RunQueue(int _priority)
    {
        priority = _priority;
    }
};

#endif