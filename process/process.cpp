#include "process.h"

Process::Process(Cycle *_cycle, bool _alive)
{
    // construcotr for save state of process.
    // get current cycle, and get the opcode from process_input
    // and get other data.
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
    line_num = process_input.operations.size();
}

Process::Process(Cycle *_cycle, string _name, bool _alive)
{
    // more, get the program name for print.
    cycle = _cycle;
    alive = _alive;
    name = _name;
    if (alive)
    {
        Input input = Input(cycle->dir, "/" + cycle->target.name);
        process_input = input.parse_process_input();
        priority = cycle->target.argument;
        pid = cycle->pid;
        cycle->memory->register_process(pid);
    }
    line_num = process_input.operations.size();
}

void Process::operate()
{
    // func for main operate.
    Operation operation;
    if (alive)
    {
        // get the data when alive.
        operation = process_input.operations.front();
        process_input.operations.pop();
    }
    int printarg;

    //TODO check if last operation
    switch (operation.code)
    // get the opcode
    {
        // execute commans according to opcodes.
    case MEM_ALLOC:
        //  allocate
        printarg = cycle->memory->allocate(pid, operation.argument);
        break;
    case MEM_ACCESS:
        // access
        printarg = cycle->memory->access(pid, operation.argument);
        break;
    case MEM_RELEASE:
        // release
        printarg = cycle->memory->release(pid, operation.argument);
        break;
    case NON_MEM:
        // do nothing
        break;
    case SLEEP:
        // sleep
        if (!process_input.operations.empty())
        {
            sleep(operation.argument);
        }
        break;
    case IOWAIT:
        // io wait
        if (!process_input.operations.empty())
        {
            iowait();
        }
        break;
    }
    // print data
    print_memory(operation, printarg);
    print_scheduler(operation, printarg);
    if (process_input.operations.empty())
        quit();
}

char *code_to_str(int code)
{
    // switch int code to string
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

void Process::print_memory(Operation operation, int printarg)
{
    // funf for print memory
    char *code_str = code_to_str(operation.code);
    FILE *write_out = fopen((cycle->dir + "/../memory.txt").c_str(), "a");
    switch (operation.code)
    {
    case MEM_ALLOC:
        fprintf(write_out, "[%d Cycle] Input: Pid[%d] Function[%s] Page ID[%d] Page Num[%d]\n", cycle->cycle, pid, code_str, printarg, operation.argument);
        break;
    case MEM_ACCESS:
    case MEM_RELEASE:
        fprintf(write_out, "[%d Cycle] Input: Pid[%d] Function[%s] Page ID[%d] Page Num[%d]\n", cycle->cycle, pid, code_str, operation.argument, printarg);
        break;
    case NON_MEM:
    case SLEEP:
    case IOWAIT:
        fprintf(write_out, "[%d Cycle] Input: Pid[%d] Function[%s]\n", cycle->cycle, pid, code_str);
        break;
    default:
        fprintf(write_out, "[%d Cycle] Input: Function[NO-OP]\n", cycle->cycle);
    }
    cycle->memory->print(write_out);
    fprintf(write_out, "\n");
    fclose(write_out);
}

void Process::print_scheduler(Operation operation, int printarg)
{
    // func for print scheduler
    FILE *write_scheduler = fopen((cycle->dir + "/../scheduler.txt").c_str(), "a");

    // line1
    fprintf(write_scheduler, "[%d Cycle] Scheduled: ", cycle->cycle);
    if (cycle->is_todo)
    {
        fprintf(write_scheduler, "%d %s (priority %d)\n", cycle->target_pid, cycle->target_name.c_str(), priority);
    }
    else
    {
        fprintf(write_scheduler, "None\n");
    }

    //line2
    int line = line_num - process_input.operations.size();
    fprintf(write_scheduler, "Runnung Process: ");
    if (alive)
    {
        fprintf(write_scheduler, "Process#%d(%d) running code %s line %d(op %d, arg %d)\n", pid, priority, name.c_str(), line, operation.code, printarg);
    }
    else
    {
        fprintf(write_scheduler, "None\n");
    }

    //line3
    for (auto iter : *cycle->run_queues)
    {
        fprintf(write_scheduler, "RunQueue %d: ", iter->priority);
        if (iter->empty())
            fprintf(write_scheduler, "Empty");
        else
        {
            for (auto node : *iter)
            {
                fprintf(write_scheduler, "%d(%s) ", node->pid, node->name.c_str());
            }
        }
        fprintf(write_scheduler, "\n");
    }

    //line4
    fprintf(write_scheduler, "SleepList: ");
    if (cycle->sleep_queue->check_empty())
    {
        fprintf(write_scheduler, "Empty");
    }
    else
    {
        for (auto iter : *cycle->sleep_queue)
        {
            fprintf(write_scheduler, "%d(%s) ", iter->process, iter->process->name.c_str());
        }
    }
    fprintf(write_scheduler, "\n");

    //line5
    fprintf(write_scheduler, "IOWait List: ");
    if (cycle->io_queue->empty())
    {
        fprintf(write_scheduler, "Empty");
    }
    else
    {
        for (auto iter : *cycle->io_queue)
        {
            fprintf(write_scheduler, "%d(%s) ", iter->pid, iter->name.c_str());
        }
    }
    fprintf(write_scheduler, "\n");

    //cycle end
    fprintf(write_scheduler, "\n");

    fclose(write_scheduler);
}

void Process::sleep(int sleep_cycle)
{
    // opcode sleep, put in sleep queue and reset cpu process.
    cycle->sleep_queue->push_process(this, sleep_cycle);
    cycle->reset_cpu_process();
}

void Process::iowait()
{
    // opcode iowait, put in io queue and reset cpu proess
    cycle->io_queue->push_back(this);
    cycle->reset_cpu_process();
}

void Process::quit()
{
    // if all opcodes execute, quit the process and clean the memory.
    cycle->memory->unregister_process(pid);
    cycle->reset_cpu_process();
}
