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

private:
    string _filepath;
    map<string, string> _configMap;
    static AutoRelease autorelase;
#if 0
    static MutexLock _mutex;
    static Configuration * m_instance;
#endif
    //改进之后
#if 1
    static mutex m_mutex;
    static std::atomic<Configuration*> m_instance;
#endif
};
}
