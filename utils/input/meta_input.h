#ifndef META_INPUT
#define META_INPUT

#include <queue>

using namespace std;

// total meta data.
struct Metadata
{
    int total_op_count;
    int virtual_memory_size;
    int physical_memory_size;
    int frame_size;
};

// struct Todo for scheduling program.
struct Todo
{
    string name;
    int cycle;
    int argument;
};

struct MetaInput
{
    Metadata metadata;
    queue<Todo> todos;
};

#endif