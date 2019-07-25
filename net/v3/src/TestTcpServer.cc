//#include "../include/Acceptor.h"
//#include "../include/TcpConnection.h"
//#include "../include/EventLoop.h"
#include "../include/TcpServer.h"


#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <iostream>
using namespace std;
using namespace wd;

//回调函数体现了扩展性
void onConnection(const TcpConnectionPtr & conn)
{
    cout << conn->toString() << "has connected!" << endl;
    conn->send("welcome to server.");
}

void onMessage(const TcpConnectionPtr & conn)
{
    //该回调函数的执行时间不能过长 
    cout << "onMessage...." << endl;
    string msg = conn->receive();
    cout << ">> receive msg from clinet : " << msg << endl;
    //业务逻辑的处理交给
    //decode
    //compute
    //encode
    conn->send(msg);
}
void onClose(const TcpConnectionPtr & conn)
{
    cout << ">> " << conn->toString() << " has closed!" << endl;
}
int main()
{
    TcpServer server("192.168.4.169", 8888);

    server.setConnsectionCallback(onConnection);
    server.setMessageCallback(onMessage);
    server.setCloseCallback(onClose);

    server.start();

    return 0;
}

