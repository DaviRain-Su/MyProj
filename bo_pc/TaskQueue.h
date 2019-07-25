#pragma once
#include "MutextLock.h"
#include "Condition.h"

#include <iostream>
#include <queue>
using std::queue;
using std::cout;
using std::endl;

class TaskQueue
{
public:
    TaskQueue(size_t quSize = 10);
    ~TaskQueue(){}

    bool empty() const;
    bool full() const;
    void push(int number);
    int pop();

private:
    size_t _queSize;
    queue<int> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
};

