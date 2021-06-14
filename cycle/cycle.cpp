#include "cycle.h"

#define TODO_INPUT "INPUT"
#define RUN_QUEUE_COUNT 10

Cycle::Cycle(MetaInput _meta_input, Argument _argument)
{
    // constructor, get the meta data and argument for get target from todo and make new memory and queue by using meta data.
    meta_input = _meta_input;
    dir = _argument.dir;
    target = meta_input.todos.front();
    memory = new Memory(meta_input.metadata, _argument.algorithm, dir);
    reset_cpu_process();
    init_queues();
}

void Cycle::init_queues()
{
    // make 9 run queues, and get each priority
    run_queues = new RunQueues();
    for (int i = 0; i < RUN_QUEUE_COUNT; i++)
    {
        run_queues->push_back(new RunQueue(i));
    }
    // make sleep queue and io queue
    sleep_queue = new SleepQueue();
    io_queue = new IoQueue();
}

void Cycle::run()
{
    // overall main program loops.
    sleep_to_run();      //check the sleep queue and if find the process waked up, put in run queue.
    if (is_todo_cycle()) //if current cycle and todo cycle are same, do io_input or scheduling.
    {
        if (is_todo_input()) //do io_input.
            io_to_run();
        else
            todo_to_run(); //get new process
        reset_target();    // set target to the next todo
    }
    run_to_cpu();              //find out which process to run
    operate();                 // exectue process's opcode.
    memory->update_ref(cycle); //for sampled lru. update reference bit.
    cycle++;
}

// main loops
void Cycle::sleep_to_run()
{
    // find the wake up process.
    vector<Process *> processes = sleep_queue->get_woke_up_processes();
    for (auto iter : processes)
    {
        // If found, put it in the run queue
        run_queues->push_by_priority(iter);
    }
}

void Cycle::io_to_run()
{
    // if it is io_input cycle. do io_input
    Process *process = io_queue->search_pid(target.argument);
    io_queue->pop();
    target_name = target.name;
    target_pid = process->pid;
    run_queues->push_by_priority(process);
}

void Cycle::todo_to_run()
{
    // if it is new process scheduling cycle. put new process to run queue.
    Process *process = new Process(this, target.name, true);
    pid++;
    target_name = target.name;
    target_pid = process->pid;
    run_queues->push_by_priority(process);
}

void Cycle::run_to_cpu()
{
    // find which process to run from priority.

    Process *tmp_process = cpu_process->process;
    cpu_process = run_queues->get_prior_process(cpu_process->process, cpu_process->time_quantum);
    if (tmp_process->alive && tmp_process->pid != cpu_process->process->pid)
    {
        run_queues->push_by_priority(tmp_process);
    }
}

void Cycle::operate()
{
    // do process's opcode.
    cpu_process->operate();
}

// cycle utilites
bool Cycle::is_todo_cycle()
{
    // check if current cycle is todo cycle
    is_todo = (target.cycle == cycle);
    return target.cycle == cycle;
}

bool Cycle::is_todo_input()
{
    // check io_input
    is_input = (target.name == TODO_INPUT);
    return target.name == TODO_INPUT;
}

void Cycle::reset_target()
{
    // set target to next todo
    meta_input.todos.pop();
    if (!meta_input.todos.empty())
        target = meta_input.todos.front();
}

void Cycle::reset_cpu_process()
{
    // cpu_process is process which in current cpu.
    // if not process exist, then set dead process.
    cpu_process = new CpuProcess(new Process(this, false));
}

bool Cycle::is_whole_queues_empty()
{
    // for program exit, check all queue and cpu_process dead.
    return run_queues->check_empty() &&
           io_queue->empty() &&
           sleep_queue->check_empty() &&
           meta_input.todos.empty() &&
           !cpu_process->process->alive;
}