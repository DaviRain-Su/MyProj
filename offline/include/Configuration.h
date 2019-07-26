#pragma once
#include <string>
#include <map>
using std::string;
using std::map;
namespace  wd
{

class Configuration
{
public:
    Configuration(const string & filepath = "../data");
    ~Configuration(){}
    
    map<string, string> & getConfigMap();
private:
    //void getDir(char * path);
    string _filepath;
    map<string, string> _configMap;
};

}
