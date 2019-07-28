#pragma once
#include "Acceptor.h"
#include "EventLoop.h"
#include "TcpConnection.h"



namespace wd{

//using TcpConnection = std::shared_ptr<TcpConnection>;
//using TcpConnectionCallback = std::function<void(const TcpConnectionCallback&)>;

class TcpServer
{

public:
    TcpServer(const string & ip, unsigned short port);
    void start();

    void setConnectionCallback(TcpConnectionCallback && cb);
    void setMessageCallback(TcpConnectionCallback && cb);
    void setCloseCallback(TcpConnectionCallback && cb);

private:
    Acceptor _acceptor;
    EventLoop _loop;
};

}// end of namespace wd
