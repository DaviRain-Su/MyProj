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
    Configuration(const string & filepath = "./conf/my.bat");
    //这里还没想好怎么处理
    // Configuration(const Configuration& other);
    void establish();
    ~Configuration(){};
public:
    static Configuration *getInstance(const string & confilename = "../conf/my.bat");
    map<string, string> & getConfigMap()
    { return _configMap; }
    string ip();
    int port();
    string enDcitPpath();
    string enIndexPath();
    string znDictPath();
    string znIndexPath();
    string cachePath();
    int threadNum();
    int bufSize();
    int initSize();
    int initTime();
    int updateTime();
   
    void print()
    {
        for(auto it = _configMap.begin(); it != _configMap.end(); ++it)
        {
            std::cout << "key: " << it->first << " val: " << it->second << std::endl; 
        }
    }
private:
    string _filepath;
    map<string, string> _configMap;
    //static mutex m_mutex;
    static MutexLock _mutex;
    static Configuration * m_instance;
    static AutoRelease autorelase;
    //改进之后
    //static std::atomic<Configuration*> m_instance;
};
}
