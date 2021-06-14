#ifndef __PROCESS_H_INCLUDE
#define __PROCESS_H_INCLUDE
#ifndef __PROCESS_H_DEFINED
#define __PROCESS_H_DEFINED
class Process;
#include "cycle.h"
#include <stdio.h>
#endif

using namespace std;

#define RUN_QUEUE_COUNT 10
#define FREE -1

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
    // class for base process
    // using processinput, get the data for process like opcode
    // and save priority, pid, total opcode, program name and using pointer
    // to get current data of cycle.
    ProcessInput process_input;
    int priority = RUN_QUEUE_COUNT;
    int pid = FREE;
    int line_num;
    string name;
    bool alive;
    Cycle *cycle;

    Process(Cycle *_cycle, bool _alive);
    Process(Cycle *_cycle, string _name, bool _alive);

    void operate();

    void print_memory(Operation operation, int printarg);
    void print_scheduler(Operation operation, int printarg);

    void sleep(int sleep_cycle);

    void iowait();

    void quit();
};

#endif