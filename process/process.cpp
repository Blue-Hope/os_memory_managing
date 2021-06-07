#include "process.h"

Process::Process(Cycle *_cycle)
{
    cycle = _cycle;
    Input input = Input(cycle->dir, cycle->target.name);
    // process_input = input.parse_process_input();
    // priority = cycle->target.argument;
    // pid = cycle->pid;
    // cycle->memory.register_process(pid);
}

void Process::operate(){
    // Operation operation = process_input.operations.front();
    // process_input.operations.pop();
    // //TODO 마지막 operation 체크
    // switch (operation.code)
    // {
    // case MEM_ALLOC:
    //     cycle->memory.allocate(pid, operation.argument);
    //     break;
    // case MEM_ACCESS:
    //     break;
    // case MEM_RELEASE:
    //     cycle->memory.release(pid, operation.argument);
    //     break;
    // case NON_MEM:
    //     break;
    // case SLEEP:
    //     if (!process_input.operations.empty())
    //     {
    //         sleep(operation.argument);
    //     }
    //     break;
    // case IOWAIT:
    //     if (!process_input.operations.empty())
    //     {
    //         iowait();
    //     }
    //     break;
    // default:
    //     throw;
    // }
    // if (process_input.operations.empty())
    //     quit();
};

void Process::sleep(int sleep_cycle)
{
    // cycle->sleep_queue.push_process(this, sleep_cycle);
    // cycle->reset_cpu_process();
}

void Process::iowait()
{
    // cycle->io_queue.push_back(this);
    // cycle->reset_cpu_process();
}

void Process::quit()
{
    // cycle->memory.unregister_process(pid);
}
