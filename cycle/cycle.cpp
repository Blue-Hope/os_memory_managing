#include "cycle.h"

using namespace std;

#define TODO_INPUT "INPUT"
#define RUN_QUEUE_COUNT 10

Cycle::Cycle(MetaInput _meta_input, Argument _argument)
{
    meta_input = _meta_input;
    dir = _argument.dir;
    target = meta_input.todos.front();
    memory = Memory(meta_input.metadata, _argument.algorithm);
    init_queues();
}

void Cycle::init_queues()
{
    for (int i = 0; i < RUN_QUEUE_COUNT; i++)
    {
        run_queues.push_back(RunQueue(i));
    }
    sleep_queue = SleepQueue();
    io_queue = IoQueue();
}

void Cycle::run()
{
    sleep_to_run();
    if (is_todo_cycle())
    {
        if (is_todo_input())
            io_to_run();
        else
            todo_to_run();
        reset_target();
    }
    run_to_cpu();
    operate();
    print();
    cycle++;
}

// main loops
void Cycle::sleep_to_run()
{
    // vector<Process *> processes = sleep_queue.get_woke_up_processes();
    // for (auto iter : processes)
    // {
    //     run_queues.push_by_priority(iter);
    // }
}

void Cycle::io_to_run()
{
    // Process *process = io_queue.search_pid(target.argument);
    // run_queues.push_by_priority(process);
}

void Cycle::todo_to_run()
{
    Process *process = new Process(this);
    // pid++;
    // run_queues.push_by_priority(process);
}

void Cycle::run_to_cpu()
{
    // cpu_process = CpuProcess(run_queues.get_prior_process(cpu_process.process));
}

void Cycle::operate()
{
    // cpu_process.operate();s
}

void Cycle::print() {}

// cycle utilites
bool Cycle::is_todo_cycle()
{
    // return target.cycle == cycle;
}

bool Cycle::is_todo_input()
{
    // return target.name == TODO_INPUT;
}

void Cycle::reset_target()
{
    // meta_input.todos.pop();
    // target = meta_input.todos.front();
}

void reset_cpu_process()
{
    // cpu_process = CpuProcess();
}