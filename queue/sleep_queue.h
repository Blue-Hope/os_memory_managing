#ifndef __SLEEP_QUEUE_H_INCLUDE
#define __SLEEP_QUEUE_H_INCLUDE
#ifndef __SLEEP_QUEUE_H_DEFINED
#define __SLEEP_QUEUE_H_DEFINED
class SleepQueue;
#include "queue.h"
#include "sleep_process.h"
#endif
class SleepQueue : public Queue<SleepProcess *>
{
    // for sleep process.
    // using new class 'sleep process' to save sleep count.
public:
    void push_process(Process *process, int sleep_cycle);

    vector<Process *> get_woke_up_processes();

    bool check_empty();
};

#endif