#include "../include/WorkProcess.h"
#include "Mydict.h"

namespace  wd
{
WorkProcess::WorkProcess(const string & msg, const TcpConnectionPtr & conn)
    : _msg(msg)
    , _conn(conn)
    {}

//运行在线程池中的一个子线程中
void WorkProcess::process()
{

    string response = _msg;
    //decode
    //computer
    //encode
    //处理业务逻辑
    //要返回给客户端的消息由线程计算线程）完成数据的发送， 在设计上来说，是不合理的
    //数据发送的工作要交给IO线程（Reactor所在的线程)完成
    //将send的函数的执行延迟到IO线程去操作
    //
    //
    //
    //
    //
    _conn->sendInLoop(response);
}




}
