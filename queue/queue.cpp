#include "queue.h"

#include "process.h"

template <typename T>
T Queue<T>::pop()
{
    T element = this->at(0);
    this->erase(this->begin());
    return element;
}

template Process *Queue<Process *>::pop();