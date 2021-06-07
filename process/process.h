#ifndef __PROCESS_H_INCLUDE
#define __PROCESS_H_INCLUDE
#ifndef __PROCESS_H_DEFINED
#define __PROCESS_H_DEFINED
class Process;
#include "cycle.h"
#endif

#define RUN_QUEUE_COUNT 10

enum Opcode
{
    MEM_ALLOC,
    MEM_ACCESS,
    MEM_RELEASE,
    NON_MEM,
    SLEEP,
    IOWAIT
};

class Process
{
public:
    ProcessInput process_input;
    int priority = RUN_QUEUE_COUNT;
    int pid;
    Cycle *cycle;

    Process();

    Process(Cycle *_cycle);

    void operate();

    void sleep(int sleep_cycle);

    void iowait();

    void quit();
};

#endif