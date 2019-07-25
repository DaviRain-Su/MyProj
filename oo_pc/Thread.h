#pragma once

#include <pthread.h>

class Thread
{
public:
    Thread()
    : _pthid(0)
    , _isRunning(false)
    {}
    virtual  ~Thread();

    void start();
    void join();    

private:
    virtual void run()=0;//待执行的任务
    static void* threadfunc(void *);

private:
    pthread_t _pthid; //线程ID
    bool _isRunning; //判断是否在运行
};

