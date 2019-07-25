#pragma once
#include "Thread.h"

class Threadpool;
class WorkThread
: public Thread
{
public:
    WorkThread(Threadpool & threadpool);
    ~WorkThread(); 
    void run();
private:
   Threadpool & _threadpool; 
};

