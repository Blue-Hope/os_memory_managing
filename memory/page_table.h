#ifndef PAGE_TABLE
#define PAGE_TABLE

#include <vector>

using namespace std;

#define FREE -1
#define INDEX_INITIALIZED -1

template <typename T, typename K>
class PageTable : public vector<T>
{
public:
    int size;

    PageTable() {}

    PageTable(int _size)
    {
        size = _size;
        for (int i = 0; i < size; i++)
        {
            this->push_back(new K());
        }
    }
};

#endif