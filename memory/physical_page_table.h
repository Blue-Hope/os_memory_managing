#ifndef PHYSICAL_PAGE_TABLE
#define PHYSICAL_PAGE_TABLE

#include <math.h>
#include "page_table.h"

#define INF 10000000

struct PhysicalPage
{
    VirtualPage *virtual_page;
    int reference_count = FREE;
};

class PhysicalPageTable : public PageTable<PhysicalPage>
{
public:
    int allocation_id = 0;
    int reference_count = 0;
    string algorithm;

    PhysicalPageTable() {}

    PhysicalPageTable(int _size, string _algorithm)
    {
        algorithm = _algorithm;
    }

    int buddy(int _size)
    {
        int k = 0;
        while (true)
        {
            if (pow(2, k - 1) < _size && pow(2, k) <= _size)
                break;
            k++;
        }
        int divided_size = pow(2, k);
        for (int i = 0; i < size; i += divided_size)
        {
            bool is_free = true;
            for (int j = 0; j < divided_size; j++)
            {
                if (this->at(i + j).virtual_page->allocation_id != FREE)
                    is_free = false;
            }
            if (is_free)
                return i;
        }
        return INDEX_INITIALIZED;
    }

    void lru()
    {
        int least_reference_count = INF;
        int least_allocation_id = INDEX_INITIALIZED;
        for (auto iter : *this)
        {
            if (iter.reference_count < least_reference_count)
            {
                least_reference_count = iter.reference_count;
                least_allocation_id = iter.virtual_page->allocation_id;
            }
        }
        replace(least_allocation_id);
    }
    void sampled() {}
    void clock() {}

    void page_replacement()
    {
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
        reference_count++;
        int start = INDEX_INITIALIZED;
        while (true)
        {
            start = buddy(_virtual_page->size);
            if (start != INDEX_INITIALIZED)
            {
                break;
            }
            page_replacement();
        }

        for (int i = 0; i < _virtual_page->size; i++)
        {
            this->at(start + i).virtual_page = _virtual_page;
            this->at(start + i).reference_count = reference_count;
            if (this->at(start + i).virtual_page->allocation_id == FREE)
            {
                this->at(start + i).virtual_page->allocation_id = allocation_id;
                allocation_id++;
            }
            this->at(start + i).virtual_page->valid = 1;
        }
    }

    void replace(int _allocation_id)
    {
        for (auto iter : *this)
        {
            if (iter.virtual_page->allocation_id == _allocation_id)
            {
                iter.virtual_page->allocation_id = FREE;
                iter.virtual_page->valid = 0;
                iter.virtual_page = NULL;
            }
        }
    }

    void release(int _allocation_id)
    {
        for (auto iter : *this)
        {
            if (iter.virtual_page->allocation_id == _allocation_id)
            {
                iter.virtual_page->page_id = FREE;
                iter.virtual_page->allocation_id = FREE;
                iter.virtual_page->valid = FREE;
                iter.virtual_page->ref = FREE;
                iter.virtual_page->size = FREE;
                iter.virtual_page = NULL;
            }
        }
    }

    void access(int _allocation_id)
    {
        reference_count++;
        for (auto iter : *this)
        {
            if (iter.virtual_page->allocation_id == _allocation_id)
                iter.reference_count == reference_count;
        }
    }
};

#endif