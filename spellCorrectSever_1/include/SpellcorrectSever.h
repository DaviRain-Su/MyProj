#pragma once
#include "Configuration.h"
#include "../include/TcpServer.h"
#include "../include/Threadpool.h"
namespace  wd
{

class WorkProcess;

class SpellcorrectSever
{
public:
    SpellcorrectSever(const string & confFileName);
    ~SpellcorrectSever() {}

    void start();//开始启动服务
    
    void stop()
    { _threadpool.stop(); }

    void onConnection(TcpConnectionPtr conn);//注册被调函数给TcpSever
    void onMessage(TcpConnectionPtr conn);//主册被调函数被Tcpsever
    void onClose(TcpConnectionPtr conn);//注册被调函数被TcpSever



private:
//    Configuration & _conf;
    TcpServer _tcpsever;
    Threadpool _threadpool;
};

}
