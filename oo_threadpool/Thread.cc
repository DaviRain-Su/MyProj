#include "Thread.h"

#include <iostream>
using std::cout;
using std::endl;


void Thread::start()
{
    //创建一个子线程
    pthread_create(&_pthid, nullptr, threadfunc, this);
    _isRunning = true;
}

void * Thread::threadfunc(void* arg)
{
    Thread * pthread  = static_cast<Thread*>(arg);
    if(pthread)
        pthread->run();

    return nullptr;
}

void Thread::join()
{
    if(_isRunning){
        pthread_join(_pthid, nullptr);
        _isRunning = false;
        //cout << "IsRunning is --- " << _isRunning << endl;
    }
}
Thread::~Thread()
{
    if(_isRunning)
        pthread_detach(_pthid);
//    cout << "IsRunning is --- " << _isRunning << endl;
}
