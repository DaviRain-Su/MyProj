#ifndef __WD_EVENTLOOP_H__
#define __WD_EVENTLOOP_H__
#include "MutextLock.h"

#include <sys/epoll.h>

#include <map>
#include <memory>
#include <vector>
#include <functional>
using std::vector;
using std::map;
using std::shared_ptr;

namespace wd{

class Acceptor;
class TcpConnection;

class EventLoop
{
public:
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
    using TcpConnectionCallback = std::function<void(const TcpConnectionPtr&)>;
    using Functor = std::function<void()>;

    EventLoop(Acceptor & acceptor);
    void loop();
    void unloop();

    void runInLoop(Functor && cd);
   
    void setConnectionCallback(TcpConnectionCallback && cb)
    { _onConnection = std::move(cb); }
    void setMessageCallback(TcpConnectionCallback && cb)
    {  _onMessage = std::move(cb); }
    void setCloseCallback(TcpConnectionCallback && cb)
    { _onClose = std::move(cb); }
private:
    void waitEpollFd();
    void handleNewConnection();
    void handleMessage(int fd);
    void handRead();

    void wakeup();
    int createEpollFd();
    int createEventFd();
    void doPendingFunctors();

    void addEpollFdRead(int fd);
    void delEpollFdRead(int fd);
    bool isConnectionClosed(int fd);

private:

    int _efd;
    int _eventfd;
    Acceptor & _acceptor;
    vector<struct epoll_event> _eventList;
    map<int, TcpConnectionPtr> _conns;
    bool _isLooping;

    MutexLock _mutex;
    vector<Functor> _pendingFunctors;

    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};
}
#endif
