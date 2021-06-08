#ifndef PHYSICAL_PAGE_TABLE
#define PHYSICAL_PAGE_TABLE

#include <math.h>
#include "virtual_page_table.h"
#include "page_table.h"

#define INF 10000000

struct PhysicalPage
{
    VirtualPage *virtual_page = new VirtualPage();
    int reference_count = INF;
};

class PhysicalPageTable : public PageTable<PhysicalPage *, PhysicalPage>
{
public:
    int allocation_id = 0;
    int reference_count = 0;
    int clock_allocation_id = -1;
    string algorithm;

    PhysicalPageTable() {}

    PhysicalPageTable(int _size, string _algorithm) : PageTable(_size)
    {
        algorithm = _algorithm;
    }

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
        while (true)
        {
            int minimal_allocation_id = INF;
            for (auto iter : *this)
            {
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

        if (_virtual_page->allocation_id == FREE)
        {
            _virtual_page->allocation_id = allocation_id;
            allocation_id++;
        }
        _virtual_page->valid = 1;

        for (int i = 0; i < get_divided_size(_virtual_page->size); i++)
        {
            this->at(start + i)->virtual_page = _virtual_page;
            this->at(start + i)->reference_count = reference_count;
        }
    }

    void replace(int _allocation_id)
    {
        for (auto iter : *this)
        {
            if (iter->virtual_page->allocation_id == _allocation_id)
            {
                iter->virtual_page->valid = 0;
                if (algorithm == "sampled" || algorithm == "clock")
                    iter->virtual_page->ref = 0;
                iter->virtual_page = new VirtualPage();
            }
        }
    }

    void release(int _allocation_id)
    {
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
        reference_count++;
        for (auto iter : *this)
        {
            if (iter->virtual_page->allocation_id == _allocation_id)
                iter->reference_count == reference_count;
        }
    }

    void access_ref(int _allocation_id)
    {
        for (auto iter : *this)
        {
            if (iter->virtual_page->allocation_id == _allocation_id)
                iter->virtual_page->ref = 1;
        }
    }

    void print()
    {
        int cnt = 1;
        printf("|");
        for (auto iter : *this)
        {
            string allocation_id = iter->virtual_page->allocation_id == FREE ? "-" : to_string(iter->virtual_page->allocation_id);
            printf("%s", allocation_id.c_str());
            if (cnt % 4 == 0)
                printf("|");
            cnt++;
        }
        printf("\n");
    }
};

#endif