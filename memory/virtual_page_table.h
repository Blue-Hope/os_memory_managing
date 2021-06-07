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
};

class VirtualPageTable : public PageTable<VirtualPage>
{
public:
    VirtualPageTable() {}

    VirtualPageTable(int _size) {}

    int pushable_index(int _size)
    {
        int start = INDEX_INITIALIZED;
        int end = INDEX_INITIALIZED;
        for (int i = 0; i < size; i++)
        {
            if (this->at(i).page_id == FREE && start == INDEX_INITIALIZED)
                start = i;

            if (this->at(i).page_id != FREE && start != INDEX_INITIALIZED && end == INDEX_INITIALIZED)
                end = i;

            if (this->at(i).page_id == FREE && start != INDEX_INITIALIZED && end == INDEX_INITIALIZED && i == size - 1)
                end = i + 1;

            if (start != INDEX_INITIALIZED && end != INDEX_INITIALIZED)
            {
                if (_size <= end - start)
                    return start;
                start = INDEX_INITIALIZED;
                end = INDEX_INITIALIZED;
            }
        }
        throw;
    };

    VirtualPage *get_virtual_page(int _page_id)
    {
        for (auto iter : *this)
        {
            if (iter.page_id == _page_id)
                return &iter;
        }
        throw;
    }

    void allocate(int _page_id, int _size)
    {
        int start = this->pushable_index(_size);
        for (int i = 0; i < _size; i++)
        {
            this->at(i).page_id = _page_id;
            this->at(i).valid = 0;
            this->at(i).size = _size;
        }
    }
};

#endif