#include "Timer.h"

#include <unistd.h>
#include <poll.h>
#include <sys/timerfd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace  wd
{

Timer::Timer(int initialTime, int intervalTime,  TimerCallback && cb)
: _timerfd(createTimerfd())
, _initialTime(initialTime)
, _intervalTime(intervalTime)
, _isStarted(false)
, _cb(std::move(cb))
    {
        std::cout << " _initialTime:  " << _initialTime
            << " _intervalTime : " << _intervalTime << std::endl;
    }

void Timer::start()
{
    _isStarted = true;

    struct pollfd pfd;
    pfd.fd = _timerfd;
    pfd.events = POLLIN;

    setTimerfd(_initialTime , _intervalTime);

    while(_isStarted){
        int nready = ::poll(&pfd, 1, 5000);
        if(nready == -1 && errno == EINTR)
            continue;
        else if(nready == -1)
            return ;
        else if(nready == 0)
            printf(">> pool timeout!!\n");
        else{
            if(pfd.revents & POLLIN)
            {
                handleRead();
                if(_cb)
                    _cb();
            }
        }
    }
}

void Timer::stop()
{
    if(_isStarted){
        _isStarted = false;
        setTimerfd(0, 0);
    }
}

int Timer::createTimerfd()
{
    int fd = ::timerfd_create(CLOCK_REALTIME, 0);
    if(fd == -1){
        perror(">> timerfd_create");
    }
    return fd;
}


void Timer::setTimerfd(int initialTime, int intervalTime)
{
    struct itimerspec value;
    value.it_value.tv_sec = initialTime;
    value.it_value.tv_nsec = 0;
    value.it_interval.tv_sec = intervalTime;
    value.it_interval.tv_nsec = 0;

    int ret = ::timerfd_settime(_timerfd, 0, &value, nullptr);
    if(ret == -1)
    {
        perror(">> timerfd_settime");
    }
    printf("***胤\n");
}

void Timer::handleRead()
{
    uint64_t howmany;
    int ret = ::read(_timerfd, &howmany, sizeof(uint64_t));
    if(ret != sizeof(howmany))
    {
        perror(">> read");
    }
}//end of namespace wd





}
