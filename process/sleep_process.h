#ifndef SLEEP_PROCESS
#define SLEEP_PROCESS

#include "process.h"

class SleepProcess
{
public:
    Process *process;
    int sleep_cycle;

    SleepProcess(Process *_process, int _sleep_cycle)
    {
        process = _process;
        sleep_cycle = _sleep_cycle;
    }
};

#endif