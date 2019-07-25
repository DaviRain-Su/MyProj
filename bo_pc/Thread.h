#pragma once

#include <pthread.h>
#include <boost/noncopyable.hpp>
#include <functional>
using std::function;


//具体类
class Thread
: boost::noncopyable

    //用到的语法规则，派生类之间赋值控制规则
    //第一：派生类显示定义了自己的赋值构造函数
    //第二: 没有显示自己的赋值构造函数,基类会调用基类的赋值构造函数，派生类会调用派生类自己
    //赋值构造函数
    //通过派生解决 不能派生的问题
    //
{

public:
    using ThreadCallback = function<void()>;
    
    //注册回调函数
    Thread(ThreadCallback && cb)
    : _pthid(0)
    , _isRunning(false)
    , _cb(std::move(cb))
    {}
     ~Thread();

    void start();
    void join();    

private:
    static void* threadfunc(void *);

private:
    pthread_t _pthid; //线程ID
    bool _isRunning; //判断是否在运行
    ThreadCallback _cb;
};

