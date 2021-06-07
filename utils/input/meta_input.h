#ifndef META_INPUT
#define META_INPUT

#include <queue>

using namespace std;

struct Metadata
{
    int total_op_count;
    int virtual_memory_size;
    int physical_memory_size;
    int frame_size;
};

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