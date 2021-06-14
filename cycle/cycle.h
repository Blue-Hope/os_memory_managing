#ifndef __CYCLE_H_INCLUDE
#define __CYCLE_H_INCLUDE
#ifndef __CYCLE_H_DEFINED
#define __CYCLE_H_DEFINED
class Cycle;
#include "input.h"
#include "argparse.h"
#include "sleep_queue.h"
#include "run_queues.h"
#include "io_queue.h"
#include "cpu_process.h"
#include "base_memory.h"
#endif

using namespace std;

#define TODO_INPUT "INPUT"
#define RUN_QUEUE_COUNT 10
#define DEFAULT_TIME_QUANTUM 10

class Cycle
{
    // Cycle header for overall program execute management.
public:
    // save current proces id, current cycle, other queue and memory.
    int pid = 0;
    int cycle = 0;
    bool is_todo;  // for print
    bool is_input; // for print
    string target_name;
    int target_pid;
    int time_quantum = DEFAULT_TIME_QUANTUM;
    string dir;
    MetaInput meta_input;
    RunQueues *run_queues;
    SleepQueue *sleep_queue;
    IoQueue *io_queue;
    CpuProcess *cpu_process;
    Todo target;
    Memory *memory;

    Cycle();
    Cycle(MetaInput _meta_input, Argument _argument);

    void init_queues();

    void run();

    void sleep_to_run();

    void io_to_run();

    void todo_to_run();

    void run_to_cpu();

    void operate();

    bool is_todo_cycle();

    bool is_todo_input();

    void reset_target();

    void reset_cpu_process();

    bool is_whole_queues_empty();
};

#endif