#ifndef MEMORY
#define MEMORY

#include <map>
#include "math.h"
#include "virtual_memory.h"
#include "physical_page_table.h"
#include <string>

using namespace std;

class Memory
{
    // base memory for manage overall memory
public:

    // using metadata for get memory size,
    // make physicalpagetable for manage physical meomory
    // and map vitrual memory for manage each pid, and access each page id
    Metadata metadata;
    PhysicalPageTable physical_memory;
    map<int, VirtualMemory> virtual_memory_map;
    int page_fault = 0;
    string dir;

    Memory() {}

    Memory(Metadata _metadata, string _algorithm, string _dir)
    {   
        // constructor for get meta data, algorith and directory
        dir = _dir;
        metadata = _metadata;
        // get physical page table.
        physical_memory = PhysicalPageTable(metadata.physical_memory_size / metadata.frame_size, _algorithm);
    }

    void register_process(int pid)
    {
        // when make new process, add to virtual memory map
        virtual_memory_map[pid] = VirtualMemory(metadata.virtual_memory_size / metadata.frame_size);
    }

    void unregister_process(int pid)
    {
        // when process execute all opcode, clean the memory and erase the page
        for(auto iter:virtual_memory_map[pid].page_table){
            release(pid, iter->page_id);
        }
        virtual_memory_map.erase(pid);
    }

    int allocate(int pid, int _size)
    {
        // call allocate opcode, allocate new memory to virtual memory
        return virtual_memory_map[pid].allocate(_size);
    }

    int release(int pid, int _page_id)
    {
        // call release opcode, find the virtual memory by using pid, page_id
        VirtualPage *virtual_page = virtual_memory_map[pid].page_table.get_virtual_page(_page_id);
        int size = virtual_page->size;
        // release physical memory
        physical_memory.release(virtual_page->allocation_id);
        // release virtual memory
        virtual_memory_map[pid].release(virtual_page->allocation_id);

        return size;
    }

    int access(int pid, int _page_id)
    {
        // access the memory, first get the virtual page by using pid, page_id
        VirtualPage *virtual_page = virtual_memory_map[pid].page_table.get_virtual_page(_page_id);
        // if valid of virtual page is 0, allocate to virtual page
        if (virtual_page->valid == 0)
        {
            physical_memory.allocate(virtual_page);
            page_fault++;
        }
        
        else
        {
            // else, access to physical memory
            physical_memory.access(virtual_page->allocation_id);
        }
            // if sampled or clodk, do other thing for ref bit.
        if (physical_memory.algorithm == "sampled" ||
            physical_memory.algorithm == "clock")
        {
            physical_memory.access_ref(virtual_page->allocation_id);
        }
        return virtual_page->size;
    }

    void update_ref(int cycle)
    {
        // update ref for sampled lru
        if (cycle % 8 == 7)
        {
            for (auto &iter : virtual_memory_map)
            {
                iter.second.update_ref();
            }
        }
    }

    void print(FILE* out)
    {
        // print
        fprintf(out, "%-29s", ">> Physical Memory: ");
        physical_memory.print(out);
        for (auto &iter : virtual_memory_map)
        {
            iter.second.print_page_id(iter.first, out);
            iter.second.print_allocation_id(iter.first, out);
            iter.second.print_valid(iter.first, out);
            iter.second.print_ref(iter.first, out);
        }
        // fprintf(out, "\n");
    }
};

#endif