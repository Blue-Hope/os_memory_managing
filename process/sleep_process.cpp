#include "sleep_process.h"

SleepProcess::SleepProcess(Process *_process, int _sleep_cycle)
{
    process = _process;
    sleep_cycle = _sleep_cycle;
}
