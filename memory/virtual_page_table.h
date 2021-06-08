#ifndef VIRTUAL_PAGE_TABLE
#define VIRTUAL_PAGE_TABLE

#include "page_table.h"

struct VirtualPage
{
    int page_id = FREE;
    int allocation_id = FREE;
    int valid = FREE;
    int ref = FREE;
    int size = FREE;
    int sample_ref = 0;
};

class VirtualPageTable : public PageTable<VirtualPage *, VirtualPage>
{
public:
    VirtualPageTable() {}

    VirtualPageTable(int _size) : PageTable(_size) {}

    int pushable_index(int _size)
    {
        int start = INDEX_INITIALIZED;
        int end = INDEX_INITIALIZED;
        for (int i = 0; i < size; i++)
        {
            if (this->at(i)->page_id == FREE && start == INDEX_INITIALIZED)
                start = i;

            if (this->at(i)->page_id != FREE)
            {
                start = INDEX_INITIALIZED;
                end = INDEX_INITIALIZED;
            }

            if (this->at(i)->page_id == FREE && start != INDEX_INITIALIZED)
                end = i;

            if (start != INDEX_INITIALIZED && end != INDEX_INITIALIZED && _size <= end - start + 1)
                return start;
        }
        throw;
    };

    VirtualPage *get_virtual_page(int _page_id)
    {
        for (auto iter : *this)
        {
            if (iter->page_id == _page_id)
                return iter;
        }
        throw;
    }

    void allocate(int _page_id, int _size)
    {
        int start = this->pushable_index(_size);

        VirtualPage *virtual_page = new VirtualPage();
        virtual_page->page_id = _page_id;
        virtual_page->valid = 0;
        virtual_page->size = _size;

        for (int i = 0; i < _size; i++)
        {
            this->at(start + i) = virtual_page;
        }
    }

    void release(int _allocation_id)
    {
        for (int i = 0; i < size; i++)
        {
            if (this->at(i)->allocation_id == _allocation_id)
                this->at(i) = new VirtualPage();
        }
    }
};

#endif