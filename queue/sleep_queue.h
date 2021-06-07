#ifndef SLEEP_QUEUE
#define SLEEP_QUEUE

#include "queue.h"
// #include "sleep_process.h"

class SleepQueue : public Queue<string>
{
public:
    // void push_process(Process *process, int sleep_cycle)
    // {
    //     SleepProcess sleep_process = SleepProcess(process, sleep_cycle);
    //     this->push_back(sleep_process);
    // }

    // vector<Process *> get_woke_up_processes()
    // {
    //     vector<Process *> processes;
    //     for (auto iter : *this)
    //     {
    //         iter.sleep_cycle -= 1;
    //         if (iter.sleep_cycle <= 0)
    //             processes.push_back(iter.process);
    //     }
    //     return processes;
    // }
};

#endif