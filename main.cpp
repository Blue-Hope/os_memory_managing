#include "cycle.h"
using namespace std;

int main(int argc, char **argv)
{
    Argument argument = Argument(argc, argv);
    Input input = Input(argument.dir, "/input");
    MetaInput meta_input = input.parse_meta_input();
    Cycle cycle = Cycle(meta_input, argument);

    while (true)
    {
        cycle.run();
        if (cycle.is_whole_queues_empty())
        {
            break;
        }
        printf("\n");
    }
    return 0;
}
