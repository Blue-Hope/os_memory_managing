#ifndef RUN_QUEUES
#define RUN_QUEUES

#include <vector>
#include "run_queue.h"
// #include "process.h"

using namespace std;

class RunQueues : public vector<RunQueue>
{
public:
    // void push_by_priority(Process *process)
    // {
    //     this->at(process->priority).push_back(process);
    // }

    // Process *get_prior_process(Process *cpu_process)
    // {
    //     for (int i = 0; i < cpu_process->priority; i++)
    //     {
    //         RunQueue run_queue = this->at(cpu_process->priority);
    //         if (!run_queue.empty())
    //             return run_queue.pop();
    //     }
    //     return cpu_process;
    // }
};

#endif