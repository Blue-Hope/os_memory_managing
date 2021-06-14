#include "io_queue.h"

Process *IoQueue::search_pid(int pid)
{
    // search_pid for  io_input event.
    for (auto iter : *this)
    {
        if (iter->pid == pid)
            return iter;
    }
    throw;
}
