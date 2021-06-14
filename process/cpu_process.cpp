#include "cpu_process.h"

using namespace std;

CpuProcess::CpuProcess(Process *_process, int _time_quantum)
{
    // constructor for save process and time quantum.
    process = _process;
    time_quantum = _time_quantum;
}

void CpuProcess::operate()
{
    // execute operate func and if the priority is low,
    // the time quantum is reducec
    process->operate();
    if (process->priority >= 5)
        time_quantum--;
    if (time_quantum <= 0)
        back_to_run();
}

void CpuProcess::back_to_run()
{
    // if time quantuam becomes 0, back to run queue.
    process->cycle->run_queues->push_by_priority(process);
    process->cycle->reset_cpu_process();
}