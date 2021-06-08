#ifndef MEMORY
#define MEMORY

#include <map>
#include "math.h"
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

    int allocate(int pid, int _size)
    {
        return virtual_memory_map[pid].allocate(_size);
    }

    int release(int pid, int _page_id)
    {
        VirtualPage *virtual_page = virtual_memory_map[pid].page_table.get_virtual_page(_page_id);
        int size = virtual_page->size;
        physical_memory.release(virtual_page->allocation_id);
        virtual_memory_map[pid].release(virtual_page->allocation_id);
        return size;
    }

    int access(int pid, int _page_id)
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
        if (physical_memory.algorithm == "sampled" ||
            physical_memory.algorithm == "clock")
        {
            physical_memory.access_ref(virtual_page->allocation_id);
        }
        return virtual_page->size;
    }

    void update_ref(int cycle)
    {
        if (cycle % 8 == 7)
        {
            for (auto &iter : virtual_memory_map)
            {
                iter.second.update_ref();
            }
        }
    }

    void print()
    {
        printf("%-29s", ">> Physical Memory: ");
        physical_memory.print();
        for (auto &iter : virtual_memory_map)
        {
            iter.second.print_page_id(iter.first);
            iter.second.print_allocation_id(iter.first);
            iter.second.print_valid(iter.first);
            iter.second.print_ref(iter.first);
        }
        printf("\n");
    }
};

#endif