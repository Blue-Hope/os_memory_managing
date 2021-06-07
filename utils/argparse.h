#ifndef ARGPARSE
#define ARGPARSE

#include <string>

using namespace std;

class Argument
{
public:
    string dir;
    string algorithm;

    Argument(int argc, char **argv)
    {

        for (int i = 1; i < argc; i++)
        {
            string s_argv(argv[i]);
            get_dir(s_argv);
            get_algorithm(s_argv);
        }
    }

    void get_dir(string s_argv)
    {
        if (s_argv.find("-dir") != -1)
        {
            dir = s_argv.substr(5, s_argv.length() - 1);
        }
    }

    void get_algorithm(string s_argv)
    {
        if (s_argv.find("-page") != -1)
        {
            algorithm = s_argv.substr(6, s_argv.length() - 1);
        }
    }
};

#endif