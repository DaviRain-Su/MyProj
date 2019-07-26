#pragma once
#include <string>
using std::string;
namespace  wd
{

class Configuration
{
public:
    Configuration(const string & confName = "../conf");
    ~Configuration(){}
    
//    const string& getconf() { return _confName; }

    const string& ip() const{ return _ip; };
    int port();
    
    const string& datafileName()  const {return _datafile;};

private:
    void establish();
    
    const string & _confName;
    string _ip;
    string _port;
    string _datafile;
};

}
