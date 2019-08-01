#pragma once
#include "../include/Thread.h"
#include "Timer.h"

namespace wd
{

class TimerThread
{
    using TimerCallback = function<void()>;
public:
    TimerThread(int initialTime, int initervalTime,TimerCallback && cb)
    : _timer(initialTime, initervalTime, std::move(cb))
    , _thread(std::bind(&Timer::start, &_timer))
    {
        _timer.print();
    }

    ~TimerThread() {}
    void start()
    {
        _timer.print();
        _thread.start();
        std::cout << "*******\n";
        _timer.print();
    }
    void stop()
    {
        _timer.stop();
        _thread.join();
    }
private:
    Timer _timer;
    Thread _thread;
};

}//end of namespace wd;
