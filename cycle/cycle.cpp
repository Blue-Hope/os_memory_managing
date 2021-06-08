#include "cycle.h"

#define TODO_INPUT "INPUT"
#define RUN_QUEUE_COUNT 10

Cycle::Cycle(MetaInput _meta_input, Argument _argument)
{
    meta_input = _meta_input;
    dir = _argument.dir;
    target = meta_input.todos.front();
    memory = new Memory(meta_input.metadata, _argument.algorithm);
    reset_cpu_process();
    init_queues();
}

void Cycle::init_queues()
{
    run_queues = new RunQueues();
    for (int i = 0; i < RUN_QUEUE_COUNT; i++)
    {
        run_queues->push_back(new RunQueue(i));
    }
    sleep_queue = new SleepQueue();
    io_queue = new IoQueue();
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
    memory->update_ref(cycle);
    cycle++;
}

// main loops
void Cycle::sleep_to_run()
{
    vector<Process *> processes = sleep_queue->get_woke_up_processes();
    for (auto iter : processes)
    {
        run_queues->push_by_priority(iter);
    }
}

void Cycle::io_to_run()
{
    Process *process = io_queue->search_pid(target.argument);
    io_queue->pop();
    run_queues->push_by_priority(process);
}

void Cycle::todo_to_run()
{
    Process *process = new Process(this, true);
    pid++;
    run_queues->push_by_priority(process);
}

void Cycle::run_to_cpu()
{
    cpu_process = run_queues->get_prior_process(cpu_process->process, cpu_process->time_quantum);
}

void Cycle::operate()
{
    cpu_process->operate();
}

// cycle utilites
bool Cycle::is_todo_cycle()
{
    return target.cycle == cycle;
}

bool Cycle::is_todo_input()
{
    return target.name == TODO_INPUT;
}

void Cycle::reset_target()
{
    meta_input.todos.pop();
    target = meta_input.todos.front();
}

void Cycle::reset_cpu_process()
{
    cpu_process = new CpuProcess(new Process(this, false));
}

bool Cycle::is_whole_queues_empty()
{
    return run_queues->check_empty() &&
           io_queue->empty() &&
           sleep_queue->check_empty() &&
           meta_input.todos.empty() &&
           !cpu_process->process->alive;
}