#include "Configuration.h"

#include <stdlib.h>

#include <fstream>
using std::ifstream;
#include <iostream>
#include <sstream>
using std::istringstream;

namespace wd{

#if 1

Configuration* Configuration::m_instance = nullptr;

Configuration::AutoRelease Configuration::autorelase{};
//双端检查锁 但由于内存读写reorder不安全
Configuration *Configuration::getInstance()
{
    if(m_instance == nullptr){
        MutexLock lock;
        if(m_instance == nullptr)
        {
            m_instance = new Configuration();
        }
    }
    return m_instance;
}


#endif





#if 0
//c++11版本之后的跨平台实现
std::atomic<Configuration*> Configuration::m_instance;
std::mutex Configuration::m_mutex;
Configuration::AutoRelease Configuration::autorelase{};

//getInstance
//
Configuration* Configuration::getInstance()
{
    Configuration * tmp = m_instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);//获取内存fence
    if(tmp == nullptr)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        tmp = m_instance.load(std::memory_order_relaxed);
            if(tmp == nullptr){
                tmp = new Configuration();
                std::atomic_thread_fence(std::memory_order_relaxed);
                m_instance.store(tmp, std::memory_order_relaxed);
            }
    }
    return tmp;
    
}
#endif


Configuration::Configuration(const string & filepath)
: _filepath(filepath)
{
    establish();
}
//读取ip port datafile
void Configuration::establish()
{
    string  line;
    
    string key;
    string val;

    std::ifstream in(_filepath);
    if(!in.good())
    {
        std::cout << ">> Cann't open file " <<_filepath << std::endl;
    }
    while(getline(in, line))
    {
        std::istringstream record(line);
        record >> key >> val;
        _configMap.insert(make_pair(key, val)); 
    }
}
}
