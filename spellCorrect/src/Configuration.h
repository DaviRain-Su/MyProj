#pragma once
#include "../include/MutextLock.h"

#include <map>
#include <string>
#include <mutex>
#include <atomic>
using std::map;
using std::string;
using std::mutex;

namespace  wd
{

class Configuration
{

    class AutoRelease
    {
    public:
        AutoRelease() {}
        ~AutoRelease(){
            if(m_instance){
                delete m_instance;
            }
        }
    };



private:
    Configuration(const string & filepath = "../conf/my.bat");
    //这里还没想好怎么处理
    // Configuration(const Configuration& other);
    void establish();
    ~Configuration(){};
public:
    static Configuration *getInstance();
    map<string, string> & getConfigMap()
    { return _configMap; }
private:
    string _filepath;
    map<string, string> _configMap;
    static mutex m_mutex;
    static Configuration * m_instance;
    static AutoRelease autorelase;
    //改进之后
    //static std::atomic<Configuration*> m_instance;
};
}
