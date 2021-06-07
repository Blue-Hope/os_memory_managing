#ifndef IO_QUEUE
#define IO_QUEUE

#include "queue.h"

class IoQueue : public Queue<string>
{
public:
    // Process *search_pid(int pid)
    // {
    //     for (auto iter : *this)
    //     {
    //         if (iter->pid == pid)
    //             return iter;
    //     }
    //     throw;
    // }
};

#endif