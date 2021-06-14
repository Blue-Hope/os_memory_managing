#ifndef INPUT
#define INPUT

#include <iostream>
#include <sstream>
#include <fstream>

#include "meta_input.h"
#include "process_input.h"

using namespace std;

// class 'input' manage meta_input and process_input.
// meta_input is for overall data from input (ex) program name, virtual mermor size ...)
// process_input is read from program input, for data for process.
class Input
{
public:
    vector<string> words;

    Input(string dir, string subdir)
    {
        readinput(dir + subdir); // constructor, call readinput.
    }

    void readinput(string path)
    {
        // func for read input file
        string line;
        ifstream stream(path);
        while (getline(stream, line))
        {
            string tmp;
            stringstream word(line);
            while (word >> tmp)
            {
                words.push_back(tmp);
            }
        }
    }

    MetaInput parse_meta_input()
    {
        // from input file, get the ovreall data.
        MetaInput meta_input;

        // first 4 words are total program num, frame size, and other memory size.
        Metadata metadata;
        metadata.total_op_count = stoi(words[0]);
        metadata.frame_size = stoi(words[3]);
        metadata.virtual_memory_size = stoi(words[1]);
        metadata.physical_memory_size = stoi(words[2]);

        // split other data. and put in class 'todo' for scheduling program.
        queue<Todo> todos;

        for (int i = 4; i < words.size(); i += 3)
        {
            Todo todo;
            todo.cycle = stoi(words[i]);
            todo.name = words[i + 1];
            todo.argument = stoi(words[i + 2]);

            todos.push(todo);
        }

        meta_input.metadata = metadata;
        meta_input.todos = todos;
        return meta_input;
    }

    ProcessInput parse_process_input()
    {
        // prcessinput is for process data like opcode and argument.
        ProcessInput process_input;

        for (int i = 1; i < stoi(words[0]) + 1; i++)
        {
            Operation operation;
            operation.code = stoi(words[2 * i - 1]);
            operation.argument = stoi(words[2 * i]);

            process_input.operations.push(operation);
        }

        return process_input;
    }
};

#endif
