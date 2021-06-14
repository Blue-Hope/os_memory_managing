#include "cycle.h"
using namespace std;

int main(int argc, char **argv)
{
    Argument argument = Argument(argc, argv); // Using Class Argument, parse argv.
    Input input = Input(argument.dir, "/input"); // Using class input, Meta input
    MetaInput meta_input = input.parse_meta_input(); // save the Metadata and Process data.
    Cycle cycle = Cycle(meta_input, argument); // make the Cycle for run.
    
    remove((argument.dir + "/../scheduler.txt").c_str()); // if there are exist output,
    remove((argument.dir + "/../memory.txt").c_str()); // remove it.
    
    while (true)
    {
        // while not todo_list empty and other queue empty, run.
        cycle.run();
        if (cycle.is_whole_queues_empty()) // if all queue empty, exit.
        {   
            FILE *write_out = fopen((argument.dir + "/../memory.txt").c_str(), "a");
            fprintf(write_out, "page fault = %d\n", cycle.memory->page_fault); // print page fault.
            fclose(write_out);
            break;
            
        }
    }
    return 0;
}
