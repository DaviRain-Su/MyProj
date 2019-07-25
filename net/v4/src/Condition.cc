
#include "../include/Condition.h"
#include "../include/MutextLock.h" //在Cnodtion的实现文件里面加载MutexLock的头文件

#include <stdio.h>
#include <errno.h>
namespace  wd
{

Condition:: Condition(MutexLock & mutex)
    : _mutex(mutex)
{
    if(pthread_cond_init(&_cond, nullptr))
    {
        perror(">> pthread_cond_init");
    }
}
void Condition::wait()
{
    if(pthread_cond_wait(&_cond, _mutex.getMutexPtr()))
    {
        perror(">> pthread_cond_wait");
    }
}
void Condition::notify()
{
    if(pthread_cond_signal(&_cond))
    {
        perror(">> pthread_cond_signal");
    }
}
void Condition::notifyAll()
{
    if(pthread_cond_broadcast(&_cond))
    {
        perror(">> pthread_cond_broadcast");
    }
}
Condition::~Condition()
{
    if(pthread_cond_destroy(&_cond))
    {
        perror(" >> pthread_cond_destroy");
    }
}
}
