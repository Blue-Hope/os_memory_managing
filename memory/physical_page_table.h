#ifndef PHYSICAL_PAGE_TABLE
#define PHYSICAL_PAGE_TABLE

#include <math.h>
#include "virtual_page_table.h"
#include "page_table.h"

#define INF 10000000

struct PhysicalPage
// set physical page for map virtual page and set ref count.
{
    VirtualPage *virtual_page = new VirtualPage();
    int reference_count = INF;
};

class PhysicalPageTable : public PageTable<PhysicalPage *, PhysicalPage>
{
public:
    // physical page table for page table vector.
    int allocation_id = 0;
    int reference_count = 0;
    int clock_allocation_id = -1;
    string algorithm;

    PhysicalPageTable() {}

    PhysicalPageTable(int _size, string _algorithm) : PageTable(_size)
    {
        algorithm = _algorithm;
    }

    // get max divided size for buddy system.
    int get_divided_size(int _size)
    {
        int k = 0;
        while (true)
        {
            if (pow(2, k - 1) < _size && _size <= pow(2, k))
                break;
            k++;
        }
        return pow(2, k);
    }

    int buddy(int _size)
    {
        // buddy system, find the proper pow(2,k) size for memory
        int divided_size = get_divided_size(_size);
        for (int i = 0; i < size; i += divided_size)
        {
            bool is_free = true;
            for (int j = 0; j < divided_size; j++)
            {
                if (this->at(i + j)->virtual_page->allocation_id != FREE)
                    is_free = false;
            }
            if (is_free)
                return i;
        }
        return INDEX_INITIALIZED;
    }

    void lru()
    {

        // lru algorithm
        int least_reference_count = INF;
        int least_allocation_id = INDEX_INITIALIZED;
        for (auto iter : *this)
        {

            if (iter->reference_count < least_reference_count)
            {
                least_reference_count = iter->reference_count;
                least_allocation_id = iter->virtual_page->allocation_id;
            }
        }
        replace(least_allocation_id);
    }

    void sampled()
    {
        // sampled lru algorithm
        int least_sampled_reference_count = INF;
        int least_allocation_id = INF;
        for (auto iter : *this)
        {
            if (iter->virtual_page->sample_ref < least_sampled_reference_count &&
                iter->virtual_page->allocation_id < least_allocation_id)
            {
                least_sampled_reference_count = iter->virtual_page->sample_ref;
                least_allocation_id = iter->virtual_page->allocation_id;
            }
        }
        replace(least_allocation_id);
    }

    void clock()
    {
        // clock algorithm.
        while (true)
        {
            int minimal_allocation_id = INF;
            for (auto iter : *this)
            {
                // sort the physical memory by aid, and search form the aid with he
                // lowest number
                if (iter->virtual_page->allocation_id < minimal_allocation_id &&
                    iter->virtual_page->allocation_id > clock_allocation_id)
                    minimal_allocation_id = iter->virtual_page->allocation_id;
            }
            if (minimal_allocation_id == INF)
            {
                clock_allocation_id = FREE;
                continue;
            }
            for (auto iter : *this)
            {
                if (iter->virtual_page->allocation_id == minimal_allocation_id)
                {
                    // Find the ref one by one and memorize the clock.
                    if (iter->virtual_page->ref == 1)
                    {
                        iter->virtual_page->ref = 0;
                        continue;
                    }
                    if (iter->virtual_page->ref == 0)
                    {
                        clock_allocation_id = iter->virtual_page->allocation_id;
                        replace(clock_allocation_id);
                        return;
                    }
                }
            }
        }
    }

    void page_replacement()
    {
        // set page replacement algorithm
        if (algorithm == "lru")
        {
            lru();
        }
        else if (algorithm == "sampled")
        {
            sampled();
        }
        else if (algorithm == "clock")
        {
            clock();
        }
    }

    void allocate(VirtualPage *_virtual_page)
    {
        // when accecss the memory, but it is not in physical memory
        // allocates new memory.
        reference_count++;
        int start = INDEX_INITIALIZED;
        while (true)
        {
            // using buddy system. find the memory space
            start = buddy(_virtual_page->size);
            if (start != INDEX_INITIALIZED)
            {
                // if ther is no space,
                // perform page replacement
                break;
            }
            page_replacement();
        }

        if (_virtual_page->allocation_id == FREE)
        {
            // get aid ++
            _virtual_page->allocation_id = allocation_id;
            allocation_id++;
        }
        // set valid of virtual page 1
        _virtual_page->valid = 1;

        for (int i = 0; i < get_divided_size(_virtual_page->size); i++)
        {
            // allocate to physical memory
            this->at(start + i)->virtual_page = _virtual_page;
            this->at(start + i)->reference_count = reference_count;
        }
    }

    void replace(int _allocation_id)
    {
        for (auto iter : *this)
        {
            // replace page to new allocated page by using page replacement algorithm
            if (iter->virtual_page->allocation_id == _allocation_id)
            {
                iter->virtual_page->valid = 0;
                iter->reference_count = INF;
                if (algorithm == "sampled" || algorithm == "clock")
                    iter->virtual_page->ref = 0;
                iter->virtual_page = new VirtualPage();
            }
        }
    }

    void release(int _allocation_id)
    {
        // release the physical memory.
        for (auto iter : *this)
        {
            if (iter->virtual_page->allocation_id == _allocation_id)
            {
                iter->virtual_page = new VirtualPage();
            }
        }
    }

    void access(int _allocation_id)
    {
        // if valid =1, just access memory.
        reference_count++;
        for (auto iter : *this)
        {
            if (iter->virtual_page->allocation_id == _allocation_id)
                iter->reference_count == reference_count;
        }
    }

    void access_ref(int _allocation_id)
    {
        // use for other algorithm.
        for (auto iter : *this)
        {
            if (iter->virtual_page->allocation_id == _allocation_id)
                iter->virtual_page->ref = 1;
        }
    }

    void print(FILE *out)
    {
        // print.
        int cnt = 1;
        fprintf(out, "|");
        for (auto iter : *this)
        {
            string allocation_id = iter->virtual_page->allocation_id == FREE ? "-" : to_string(iter->virtual_page->allocation_id);
            fprintf(out, "%s", allocation_id.c_str());
            if (cnt % 4 == 0)
                fprintf(out, "|");
            cnt++;
        }
        fprintf(out, "\n");
    }
};

#endif