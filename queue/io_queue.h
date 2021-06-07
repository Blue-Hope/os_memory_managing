#ifndef __IO_QUEUE_H_INCLUDE
#define __IO_QUEUE_H_INCLUDE
#ifndef __IO_QUEUE_H_DEFINED
#define __IO_QUEUE_H_DEFINED
class IoQueue;
#include "queue.h"
#include "process.h"
#endif

class IoQueue : public Queue<Process *>
{
public:
    Process *search_pid(int pid);
};

#endif