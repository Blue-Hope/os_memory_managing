#ifndef __QUEUE_H_INCLUDE
#define __QUEUE_H_INCLUDE
#ifndef __QUEUE_H_DEFINED
#define __QUEUE_H_DEFINED
template <typename T>
class Queue;
#include <queue>
#include <vector>
#endif

using namespace std;

template <typename T>
class Queue : public vector<T>
{
public:
    T pop();
};

#endif