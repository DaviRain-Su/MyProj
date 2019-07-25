#include "Threadpool.h"
#include "WorkThread.h"

#include <time.h>

#include <iostream>
using std::cout;
using std::endl;


Threadpool::Threadpool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _taskque(queSize)
, _isExit(false)
{
    _threads.reserve(_threadNum);
}

Threadpool::~Threadpool()
{
    if(!_isExit)
        stop();
}
void Threadpool::start()
{
    //创建线程对象
    for(size_t idx = 0; idx != _threadNum; ++idx){
        unique_ptr<Thread> thread(new WorkThread(*this));
        _threads.push_back(std::move(thread));
    }
    //开启线程
    for(auto & thread : _threads)
    {
        thread->start();
    }
}
void Threadpool::stop()
{
    if(!_isExit)
    {
       while(!_taskque.empty()){
           ::sleep(1);
       }
        _isExit = true;

        _taskque.wakeup();

        for(auto & thread : _threads)
            thread->join();
    }
}
void Threadpool::addTask(Task* task)
{
    _taskque.push(task);
}

Task* Threadpool::getTask()
{
    return _taskque.pop();
}

//每一个子线程要完成的任务. 其运行在
//workerThread的run方法中
void Threadpool::threadfunc()
{
    while(!_isExit)
    {
        Task* task = getTask();
        //当任务执行的速度过快
        //在还没有将_isExit设置为true之前，，每一个子线程已经
        //阻塞在getTask()之上;
        //
        if(task)
            task->process();
    }
}
