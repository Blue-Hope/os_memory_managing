#ifndef __RUN_QUEUES_H_INCLUDE
#define __RUN_QUEUES_H_INCLUDE
#ifndef __RUN_QUEUES_H_DEFINED
#define __RUN_QUEUES_H_DEFINED
class RunQueues;
#include <vector>
#include "run_queue.h"
#include "cpu_process.h"
#endif

using namespace std;

class RunQueues : public vector<RunQueue *>
{
public:
    void push_by_priority(Process *process);

    CpuProcess *get_prior_process(Process *cpu_process, int time_quantum);

    bool check_empty();
};

#endif