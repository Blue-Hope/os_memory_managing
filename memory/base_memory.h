#ifndef MEMORY
#define MEMORY

#include <map>
#include "virtual_memory.h"
#include "physical_page_table.h"

using namespace std;

class Memory
{
public:
    Metadata metadata;
    PhysicalPageTable physical_memory;
    map<int, VirtualMemory> virtual_memory_map;

    Memory() {}

    Memory(Metadata _metadata, string _algorithm)
    {
        metadata = _metadata;
        physical_memory = PhysicalPageTable(metadata.physical_memory_size / metadata.frame_size, _algorithm);
    }

    void register_process(int pid)
    {
        virtual_memory_map[pid] = VirtualMemory(metadata.virtual_memory_size / metadata.frame_size);
    }

    void unregister_process(int pid)
    {
        virtual_memory_map.erase(pid);
    }

    void allocate(int pid, int _size)
    {
        virtual_memory_map[pid].allocate(_size);
    }

    void release(int pid, int _page_id)
    {
        VirtualPage *virtual_page = virtual_memory_map[pid].page_table.get_virtual_page(_page_id);
        physical_memory.release(virtual_page->allocation_id);
    }

    void access(int pid, int _page_id)
    {
        VirtualPage *virtual_page = virtual_memory_map[pid].page_table.get_virtual_page(_page_id);
        if (virtual_page->valid == 0)
        {
            physical_memory.allocate(virtual_page);
        }
        else
        {
            physical_memory.access(virtual_page->allocation_id);
        }
    }
};

#endif