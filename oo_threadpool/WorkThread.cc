#include "WorkThread.h"

#include "Threadpool.h"

#include <iostream>
using std::cout;
using std::endl;

WorkThread::WorkThread(Threadpool & threadpool)
: _threadpool(threadpool)
{
    cout << "WorkThread()" << endl;
}
WorkThread::~WorkThread()
{
    cout << "~WorkThread()" << endl;
}
void WorkThread::run()
{
    _threadpool.threadfunc();
}
