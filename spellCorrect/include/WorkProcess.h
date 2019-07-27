#pragma once
#include "../include/TcpConnection.h"

#include <string>
using std::string;



namespace wd
{

class WorkProcess
{
public:
    WorkProcess(const string & msg, const TcpConnectionPtr & conn);

    ~WorkProcess() {}
    
    void process();

private:
    string _msg;
    TcpConnectionPtr _conn;
};

}
