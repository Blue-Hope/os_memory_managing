#include "sleep_queue.h"

void SleepQueue::push_process(Process *process, int sleep_cycle)
{
    // set process to new Sleep process and push.
    SleepProcess *sleep_process = new SleepProcess(process, sleep_cycle);
    this->push_back(sleep_process);
}

vector<Process *> SleepQueue::get_woke_up_processes()
{
    // find the process which sleep count is 0.
    // put it in vector and return vector.
    vector<Process *> processes;
    for (auto iter : *this)
    {
        iter->sleep_cycle -= 1;
        if (iter->process->alive && iter->sleep_cycle <= 0)
        {
            processes.push_back(iter->process);
            iter->process = new Process(iter->process->cycle, false);
        }
    }
    return processes;
}

bool SleepQueue::check_empty()
{
    // check if empty.
    bool is_empty = true;
    for (auto iter : *this)
    {
        is_empty = is_empty && !iter->process->alive;
    }
    return is_empty;
}