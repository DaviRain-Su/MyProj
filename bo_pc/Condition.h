#pragma once
#include "MutextLock.h"

#include <iostream>
using std::cout;
using std::endl;

class Condition
{
public:
    Condition(MutexLock & mutex)
    : _mutex(mutex)
    {
        if(pthread_cond_init(&_cond, nullptr))
        {
            perror(">> pthread_cond_init");
        }
    }
    void wait()
    {
        if(pthread_cond_wait(&_cond, _mutex.getMutexPtr()))
        {
            perror(">> pthread_cond_wait");
        }
    }
    void notify()
    {
        if(pthread_cond_signal(&_cond))
        {
            perror(">> pthread_cond_signal");
        }
    }
    void notifyAll()
    {
        if(pthread_cond_broadcast(&_cond))
        {
            perror(">> pthread_cond_broadcast");
        }
    }
    ~Condition()
    {
        if(pthread_cond_destroy(&_cond))
        {
            perror(" >> pthread_cond_destroy");
        }
    }

private:

    pthread_cond_t _cond;
    MutexLock & _mutex;
};

