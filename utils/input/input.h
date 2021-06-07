#ifndef INPUT
#define INPUT

#include <iostream>
#include <sstream>
#include <fstream>

#include "meta_input.h"
#include "process_input.h"

using namespace std;

class Input
{
public:
    vector<string> words;

    Input(string dir, string subdir)
    {
        readinput(dir + subdir);
    }

    void readinput(string path)
    {
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
        MetaInput meta_input;

        Metadata metadata;
        metadata.total_op_count = stoi(words[0]);
        metadata.frame_size = stoi(words[3]);
        metadata.virtual_memory_size = stoi(words[1]);
        metadata.physical_memory_size = stoi(words[2]);

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
        ProcessInput process_input;

        for (int i = 1; i < stoi(words[0]); i += 2)
        {
            Operation operation;
            operation.code = stoi(words[i]);
            operation.argument = stoi(words[i + 1]);

            process_input.operations.push(operation);
        }

        return process_input;
    }
};

#endif