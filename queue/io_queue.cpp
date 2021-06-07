#include "io_queue.h"

Process *IoQueue::search_pid(int pid)
{
    for (auto iter : *this)
    {
        if (iter->pid == pid)
            return iter;
    }
    throw;
}
