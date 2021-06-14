#include "queue.h"

#include "process.h"

template <typename T>
T Queue<T>::pop()
{
    // a new pop for a queue inpemented as a vector.
    T element = this->at(0);
    this->erase(this->begin());
    return element;
}

template Process *Queue<Process *>::pop();