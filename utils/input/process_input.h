#ifndef PROCESS_INPUT
#define PROCESS_INPUT

#include <queue>

using namespace std;

#define FREE -1

struct Operation
{
    int code = FREE;
    int argument;
};
struct ProcessInput
{
    queue<Operation> operations;
};

#endif