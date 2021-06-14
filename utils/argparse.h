#ifndef ARGPARSE
#define ARGPARSE

#include <string>
#include <stdio.h>
#include <unistd.h>

using namespace std;

class Argument
{
public:
    char *cwd;
    string dir;
    string algorithm = "lru";

    Argument(int argc, char **argv)
    {
        // parse argc & argv, default dir & algorithm value are current directory and LRU.
        string dir_tmp(get_current_dir_name());
        dir_tmp += "/input";
        dir = dir_tmp;
        for (int i = 1; i < argc; i++)
        {
            // if argc > 1, get dir or algorithm.
            string s_argv(argv[i]);
            get_dir(s_argv);
            get_algorithm(s_argv);
        }
    }

    void get_dir(string s_argv)
    {
        // get direcotry from argv.
        if (s_argv.find("-dir") != -1)
        {
            dir = s_argv.substr(5, s_argv.length() - 1);
        }
    }

    void get_algorithm(string s_argv)
    {
        // get algorithm from argv.
        if (s_argv.find("-page") != -1)
        {
            algorithm = s_argv.substr(6, s_argv.length() - 1);
        }
    }
};

#endif
