#include "../include/SpellcorrectSever.h"
#include "../include/WorkProcess.h"
//#include "../include/log4cpp.h"

#include "CacheManger.h"
#include <functional>
#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

SpellcorrectSever::SpellcorrectSever(const string & confFileName)
: _tcpsever(Configuration::getInstance(confFileName)->ip(), Configuration::getInstance(confFileName)->port())
, _threadpool(Configuration::getInstance(confFileName)->threadNum(),Configuration::getInstance(confFileName)->initSize())
    {
        cout << "SpellcorrectSever()" << endl;
    }

void SpellcorrectSever::start()
{

    _threadpool.start();
    
    /* cout << "init cache" << endl; */
    /* CacheManger::initCache(); */
    /* CacheManger::periodicUpdateCache(); */
    /* cout << "init cache end" << endl; */

    _tcpsever.setConnectionCallback(std::bind(&SpellcorrectSever::onConnection, this, std::placeholders::_1));
    _tcpsever.setMessageCallback(std::bind(&SpellcorrectSever::onMessage, this,std::placeholders::_1));
    _tcpsever.setCloseCallback(std::bind(&SpellcorrectSever::onClose,this, std::placeholders::_1));
    
    _tcpsever.start();
}
/*连接时需要做的任务*/
void SpellcorrectSever::onConnection(TcpConnectionPtr conn)
{
    cout << conn->toString() << " has connected!" << endl;
    conn->send("Welcome to SpellcorrectSever.");
}
/*发送信息时需要做的事情*/
void SpellcorrectSever::onMessage(TcpConnectionPtr conn)
{
    cout << "onMessage...." << endl;
    string msg = conn->receive();
    cout << ">> receive msg from client: " << msg << endl;
    

    WorkProcess work(msg, conn);
    
    _threadpool.addTask(std::bind(&WorkProcess::process, work));
}
/*关闭时需要做的任务*/
void SpellcorrectSever::onClose(TcpConnectionPtr conn)
{
    cout << "onClose...." << endl;
    cout << conn->toString() << " has closed!" << endl;
}

}
