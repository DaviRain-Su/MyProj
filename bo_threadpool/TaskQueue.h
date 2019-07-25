#pragma once
#include "MutextLock.h"
#include "Condition.h"

#include <iostream>
#include <queue>
#include <functional>

using std::queue;
using std::cout;
using std::endl;

using Task = std::function<void()>;
using ElemType = Task;

class TaskQueue
{
public:
    TaskQueue(size_t quSize = 10);
    ~TaskQueue(){}

    bool empty() const;
    bool full() const;
    void push(ElemType number);
    ElemType pop();
    
    void wakeup();
private:
    size_t _queSize;
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
    bool flag;//add
};

