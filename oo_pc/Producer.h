#pragma once
#include "Thread.h"

#include <iostream>

using std::endl;
using std::cout;

class TaskQueue;

class Producer
: public Thread
{

public:
    Producer(TaskQueue & que)
        :_que(que)
    {}

private:
    void run();

private:
    TaskQueue & _que;
};

