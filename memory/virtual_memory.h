#ifndef VIRTUAL_MEMORY
#define VIRTUAL_MEMORY

#include "virtual_page_table.h"

#define REF_BYTE_SIZE 8

using namespace std;

class VirtualMemory
{
public:
    // manage virtual memory for process level.
    VirtualPageTable page_table;
    int page_id = 0;

    VirtualMemory() {}

    VirtualMemory(int size)
    {
        page_table = VirtualPageTable(size);
    }

    int allocate(int _size)
    {
        // allocate new memory.
        page_table.allocate(page_id, _size);
        page_id++;
        return page_id - 1;
    }

    void release(int _allocation_id)
    {
        page_table.release(_allocation_id);
    }

    void update_ref()
    {
        // update ref for sampled algorithm.
        for (auto iter : page_table)
        {
            int new_sample_ref = 0;
            if (iter->ref == 1)
            {
                new_sample_ref += pow(2, 8);
            }
            iter->sample_ref /= 2;
            iter->sample_ref += new_sample_ref;
        }
    }

    void print_page_id(int pid, FILE* out)
    {
        fprintf(out, ">> pid(%d)%-20s", pid, " Page Table(PID): ");
        int cnt = 1;
        fprintf(out, "|");
        for (auto iter : page_table)
        {
            string page_id = iter->page_id == FREE ? "-" : to_string(iter->page_id);
            fprintf(out, "%s", page_id.c_str());
            if (cnt % 4 == 0)
                fprintf(out, "|");
            cnt++;
        }
        fprintf(out, "\n");
    }

    void print_allocation_id(int pid, FILE* out)
    {
        // print.
        fprintf(out, ">> pid(%d)%-20s", pid, " Page Table(AID): ");
        int cnt = 1;
        fprintf(out,"|");
        for (auto iter : page_table)
        {
            string allocation_id = iter->allocation_id == FREE ? "-" : to_string(iter->allocation_id);
            fprintf(out, "%s", allocation_id.c_str());
            if (cnt % 4 == 0)
                fprintf(out, "|");
            cnt++;
        }
        fprintf(out, "\n");
    }

    void print_valid(int pid, FILE* out)
    {
        // print.
        fprintf(out, ">> pid(%d)%-20s", pid, " Page Table(Valid): ");
        int cnt = 1;
        fprintf(out, "|");
        for (auto iter : page_table)
        {
            string valid = iter->valid == FREE ? "-" : to_string(iter->valid);
            fprintf(out, "%s", valid.c_str());
            if (cnt % 4 == 0)
                fprintf(out, "|");
            cnt++;
        }
        fprintf(out, "\n");
    }

    void print_ref(int pid, FILE* out)
    {
        // print.
        fprintf(out, ">> pid(%d)%-20s", pid, " Page Table(Ref): ");
        int cnt = 1;
        fprintf(out, "|");
        for (auto iter : page_table)
        {
            string ref = iter->ref == FREE ? "-" : to_string(iter->ref);
            fprintf(out, "%s", ref.c_str());
            if (cnt % 4 == 0)
                fprintf(out, "|");
            cnt++;
        }
        fprintf(out, "\n");
    }
};

#endif