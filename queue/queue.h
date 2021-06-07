#ifndef QUEUE
#define QUEUE

#include <queue>
#include <vector>

using namespace std;

template <typename T>
class Queue : public vector<T>
{
public:
    T pop()
    {
        T element = this->at(0);
        this->erase(this->begin());
        return element;
    }
};

#endif