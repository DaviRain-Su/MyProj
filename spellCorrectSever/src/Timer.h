#pragma once
#include <functional>
using  std::function;


namespace wd
{

class Timer
{
public:
    using TimerCallback = function<void()>;

    Timer(int initialTime, int intervalTime, TimerCallback && cd);

    ~Timer() {}
    
    void start();
    void stop();
private:
    int createTimerfd();
    void setTimerfd(int initialTime, int intervalTime);
    void handleRead();

private:
    int _timerfd;
    int _initialTime;
    int _intervalTime;

    bool _isStarted;
    TimerCallback _cb;
};

}
