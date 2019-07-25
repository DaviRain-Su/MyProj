#pragma once
#include <iostream>
#include <cstdio>
#include <boost/noncopyable.hpp>
#include <pthread.h>
#include <assert.h>

#define CHECK(exp) if(!exp)\
{\
    fprintf(stderr, "File:%s, Line: %d Exp:[" #exp "] is true, abort.\n", __FILE__, __LINE__);\
    abort();\
}

class MutexLock
: public boost::noncopyable
{
    friend class Condition;//条件变量友元声明
public:
    MutexLock();
    ~MutexLock();

    void lock();
    void unlock();

    bool isLocking() const
    { return _isLocking;  }
    
    pthread_mutex_t * getMutexPtr()
    { return & _mutex; }
private:
    void restoreMutexStatus()
    { _isLocking = true; }

    pthread_mutex_t _mutex;//互斥锁
    bool _isLocking;

};
//RAII
class MutexLockGuard
: public boost::noncopyable
{
public:
    MutexLockGuard(MutexLock &mutex)
    :_mutex(mutex)//构造时加锁
    {
        _mutex.lock();
    }
    ~MutexLockGuard()//析构时解锁
    {
        _mutex.unlock();
    }
private:
    MutexLock &_mutex;
};

