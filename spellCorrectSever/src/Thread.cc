#include "../include/Thread.h"

#include <iostream>
using std::cout;
using std::endl;

namespace  wd
{
namespace  current_thread
{
    __thread const char * threadName = "0";
}//
struct ThreadDate
{
    using ThreadCallback = function<void()>;
    ThreadDate(const string & name, const ThreadCallback & cb)
    : _name(name)
    , _cb(cb)
    {}

    string _name;
    ThreadCallback _cb;

    void runInThread()
    {
        current_thread::threadName = _name == string() ? "0" : _name.c_str();
        if(_cb)
            _cb();
    }
};
void Thread::start()
{
    ThreadDate * threadData = new ThreadDate(_name, _cb);
    //创建一个子线程
    pthread_create(&_pthid, nullptr, threadfunc, threadData);
    _isRunning = true;
}

void * Thread::threadfunc(void* arg)
{
    //Thread * pthread  = static_cast<Thread*>(arg);
    ThreadDate * threadData = static_cast<ThreadDate*> (arg);
    if(threadData)
        threadData->runInThread();
    
    delete threadData;
    
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
}// end of namespace wd
