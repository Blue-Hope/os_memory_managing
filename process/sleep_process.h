#ifndef __SLEEP_PROCESS_H_INCLUDE
#define __SLEEP_PROCESS_H_INCLUDE
#ifndef __SLEEP_PROCESS_H_DEFINED
#define __SLEEP_PROCESS_H_DEFINED
class SleepProcess;
#include "process.h"
#endif

class SleepProcess
{
public:
    Process *process;
    int sleep_cycle;

    SleepProcess(Process *_process, int _sleep_cycle);
};

#endif