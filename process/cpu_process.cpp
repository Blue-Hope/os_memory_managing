#include "cpu_process.h"

using namespace std;

CpuProcess::CpuProcess(Process *_process, int _time_quantum)
{
    process = _process;
    time_quantum = _time_quantum;
}

void CpuProcess::operate()
{
    process->operate();
    if (process->priority >= 5)
        time_quantum--;
    if (time_quantum <= 0)
        back_to_run();
}

void CpuProcess::back_to_run()
{
    process->cycle->run_queues->push_by_priority(process);
    process->cycle->reset_cpu_process();
}