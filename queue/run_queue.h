#ifndef __RUN_QUEUE_H_INCLUDE
#define __RUN_QUEUE_H_INCLUDE
#ifndef __RUN_QUEUE_H_DEFINED
#define __RUN_QUEUE_H_DEFINED
class RunQueue;
#include "queue.h"
#include "process.h"
#endif

using namespace std;

class RunQueue : public Queue<Process *>
{
public:
    int priority;

    // run queue for get process by each priority
    RunQueue(int _priority);
};

#endif