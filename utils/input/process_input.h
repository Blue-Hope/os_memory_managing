#ifndef PROCESS_INPUT
#define PROCESS_INPUT

#include <queue>

using namespace std;

#define FREE -1

// save the opcode and argumet by struct 'Operaiotn'
struct Operation
{
    int code = FREE;
    int argument;
};

// and using queue, save operation.
struct ProcessInput
{
    queue<Operation> operations;
};

#endif