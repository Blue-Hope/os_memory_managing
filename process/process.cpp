#include "process.h"

Process::Process(Cycle *_cycle, bool _alive)
{
    cycle = _cycle;
    alive = _alive;
    if (alive)
    {
        Input input = Input(cycle->dir, "/" + cycle->target.name);
        process_input = input.parse_process_input();
        priority = cycle->target.argument;
        pid = cycle->pid;
        cycle->memory->register_process(pid);
    }
}

void Process::operate()
{
    Operation operation;
    if (alive)
    {
        operation = process_input.operations.front();
        process_input.operations.pop();
    }
    int printarg;

    //TODO 마지막 operation 체크
    switch (operation.code)
    {
    case MEM_ALLOC:
        printarg = cycle->memory->allocate(pid, operation.argument);
        break;
    case MEM_ACCESS:
        printarg = cycle->memory->access(pid, operation.argument);
        break;
    case MEM_RELEASE:
        printarg = cycle->memory->release(pid, operation.argument);
        break;
    case NON_MEM:
        break;
    case SLEEP:
        if (!process_input.operations.empty())
        {
            sleep(operation.argument);
        }
        break;
    case IOWAIT:
        if (!process_input.operations.empty())
        {
            iowait();
        }
        break;
    }
    print(operation, printarg);
    if (process_input.operations.empty())
        quit();
}

char *code_to_str(int code)
{
    switch (code)
    {
    case MEM_ALLOC:
        return "ALLOCATION";
    case MEM_ACCESS:
        return "ACCESS";
    case MEM_RELEASE:
        return "RELEASE";
    case NON_MEM:
        return "NON-MEMORY";
    case SLEEP:
        return "SLEEP";
    case IOWAIT:
        return "IOWAIT";
    default:
        return "NO-OP";
    }
}

void Process::print(Operation operation, int printarg)
{
    char *code_str = code_to_str(operation.code);
    switch (operation.code)
    {
    case MEM_ALLOC:
        printf("[%d Cycle] Input: Pid[%d] Function[%s] Page ID[%d] Page Num[%d]\n", cycle->cycle, pid, code_str, printarg, operation.argument);
        break;
    case MEM_ACCESS:
    case MEM_RELEASE:
        printf("[%d Cycle] Input: Pid[%d] Function[%s] Page ID[%d] Page Num[%d]\n", cycle->cycle, pid, code_str, operation.argument, printarg);
        break;
    case NON_MEM:
    case SLEEP:
    case IOWAIT:
        printf("[%d Cycle] Input: Pid[%d] Function[%s]\n", cycle->cycle, pid, code_str);
        break;
    default:
        printf("[%d Cycle] Input: Function[NO-OP]\n", cycle->cycle);
    }
    cycle->memory->print();
}

void Process::sleep(int sleep_cycle)
{
    cycle->sleep_queue->push_process(this, sleep_cycle);
    cycle->reset_cpu_process();
}

void Process::iowait()
{
    cycle->io_queue->push_back(this);
    cycle->reset_cpu_process();
}

void Process::quit()
{
    cycle->memory->unregister_process(pid);
    cycle->reset_cpu_process();
}
