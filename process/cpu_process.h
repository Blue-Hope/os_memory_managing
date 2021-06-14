#ifndef __CPU_PROCESS_H_INCLUDE
#define __CPU_PROCESS_H_INCLUDE
#ifndef __CPU_PROCESS_H_DEFINED
#define __CPU_PROCESS_H_DEFINED
class CpuProcess;
#include "process.h"
#endif

#define DEFAULT_TIME_QUANTUM 10
using namespace std;

class CpuProcess
{
    // for the currntly runnung process
    // save the time quantum.
public:
    Process *process;
    int time_quantum = DEFAULT_TIME_QUANTUM;

    CpuProcess() {}

    CpuProcess(Process *_process, int time_quantum = DEFAULT_TIME_QUANTUM);

    void operate();

    void back_to_run();
};

#endif