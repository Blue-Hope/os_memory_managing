#ifndef __CYCLE_H_INCLUDE
#define __CYCLE_H_INCLUDE
#ifndef __CYCLE_H_DEFINED
#define __CYCLE_H_DEFINED
class Cycle;
#include "input.h"
#include "argparse.h"
#include "run_queues.h"
#include "sleep_queue.h"
#include "io_queue.h"
#include "cpu_process.h"
#include "base_memory.h"
#endif

using namespace std;

#define TODO_INPUT "INPUT"
#define RUN_QUEUE_COUNT 10

class Cycle
{
public:
    int pid = 0;
    int cycle = 0;
    int time_quantum = DEFAULT_TIME_QUANTUM;
    string dir;
    MetaInput meta_input;
    RunQueues run_queues;
    SleepQueue sleep_queue;
    IoQueue io_queue;
    CpuProcess cpu_process;
    Todo target;
    Memory memory;

    Cycle();
    Cycle(MetaInput _meta_input, Argument _argument);

    void init_queues();

    void run();

    void sleep_to_run();

    void io_to_run();

    void todo_to_run();

    void run_to_cpu();

    void operate();

    void print();

    bool is_todo_cycle();

    bool is_todo_input();

    void reset_target();

    void reset_cpu_process();
};

#endif