#ifndef PROCESS_INPUT
#define PROCESS_INPUT

#include <queue>

using namespace std;

struct Operation
{
    int code;
    int argument;
};
struct ProcessInput
{
    queue<Operation> operations;
};

#endif