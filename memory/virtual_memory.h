#ifndef VIRTUAL_MEMORY
#define VIRTUAL_MEMORY

#include "virtual_page_table.h"

using namespace std;

class VirtualMemory
{
public:
    VirtualPageTable page_table;
    int page_id = 0;

    VirtualMemory() {}

    VirtualMemory(int size)
    {
        page_table = VirtualPageTable(size);
    }

    void allocate(int _size)
    {
        page_table.allocate(page_id, _size);
        page_id++;
    }
};

#endif