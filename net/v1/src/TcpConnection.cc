
#include "../include/TcpConnection.h"
#include "../include/InetAddress.h"

#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <sstream>
#include <iostream>
using namespace std;

namespace wd
{
TcpConnection::TcpConnection(int fd)
: _sock(fd)
, _socketIo(fd)
, _localAddr(getLocalAddr())
, _peerAddr(getPeerAddr())
, _isShutdwonWrite(false)
{}

TcpConnection::~TcpConnection()
{
	if(!_isShutdwonWrite) {
		shutdown();
	}
    cout << "~TcpConnection()" << endl;
}

string TcpConnection::receive()
{
	char buff[65536] = {0};
    int ret = _socketIo.readline(buff, sizeof(buff));
//    cout << ">> ret = " << ret << endl;
	return string(buff);
}
	
void TcpConnection::send(const string & msg)
{
	_socketIo.writen(msg.c_str(), msg.size());
}

void TcpConnection::shutdown()
{
	if(!_isShutdwonWrite) {
		_isShutdwonWrite = true;
		_sock.shutdownWrite();
	}
}

string TcpConnection::toString() const
{
	std::ostringstream oss;
	oss << _localAddr.ip() << ":" << _localAddr.port() << " --> "
		<< _peerAddr.ip() << ":" << _peerAddr.port();
	return oss.str();
}


InetAddress TcpConnection::getLocalAddr()
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr);
	if(getsockname(_sock.fd(), (struct sockaddr*)&addr, &len) == -1) {
		perror("getsockname");
	}
	return InetAddress(addr);
}

InetAddress TcpConnection::getPeerAddr()
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr);
	if(getpeername(_sock.fd(), (struct sockaddr*)&addr, &len) == -1) {
		perror("getpeername");
	}
	return InetAddress(addr);
}
//设置回调函数
void TcpConnection::setConnectionCallback(const TcpConnectionCallback & cb)
{
    _onConnection = std::move(cb);
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback & cb)
{
    _onMessage = std::move(cb);
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback & cb)
{
    _onClose = std::move(cb);
}


//这里是什么呢？*******
void TcpConnection::handleConnectionCallback()
{
    if(_onConnection){
        _onConnection(shared_from_this());
    }
}
void TcpConnection::handleMessageCallback()
{
    if(_onMessage){
        _onMessage(shared_from_this());
    }
}
void TcpConnection::handleCloseCallback()
{
    if(_onClose)
    {
        _onClose(shared_from_this());
    }
}
}//end of namespace wd
