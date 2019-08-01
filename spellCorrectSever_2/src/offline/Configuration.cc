#include "../../include/Configuration.h"

#include <stdlib.h>

#include <fstream>
using std::ifstream;
#include <iostream>
#include <sstream>
using std::istringstream;

//-----
using std::cout;
using std::endl;
//---龍

namespace wd{


string Configuration::ip()
{
    auto iter_my_ip = getConfigMap().find("my_ip");
    
    return iter_my_ip->second;
}
int Configuration::port()
{
    map<string,string> mapTmp = getConfigMap();
//    auto iter_my_port = mapTmp.find("my_port");
    //----------
    cout << " 这里是去庐阳的测试" << endl;
    cout << "myPort = " << mapTmp["my_port"] << endl;
    //---------龍
   // return std::stoi(iter_my_port->second);
    return std::stoi(mapTmp["my_port"]);
}

string Configuration::enDcitPpath()
{
    auto iter_my_dict = getConfigMap().find("my_dict");

    return iter_my_dict->second;
}
string Configuration::enIndexPath()
{
    auto iter_my_index = getConfigMap().find("my_index");

    return iter_my_index->second;
}
string Configuration::znDictPath()
{
    auto iter_my_cn_dict = getConfigMap().find("my_cn_dict");
    
    return iter_my_cn_dict->second;
}
string Configuration::znIndexPath()
{
    auto iter_my_cn_index = getConfigMap().find("my_cn_index");

    return iter_my_cn_index->second;
}
string Configuration::cachePath()
{
    auto iter_my_cache = getConfigMap().find("my_cache");

    return iter_my_cache->second;
}


int Configuration::threadNum()
{
    auto iter_my_thread_num = getConfigMap().find("my_thread_num");
    
    return std::stoi(iter_my_thread_num->second);

}

int Configuration::bufSize()
{
    auto iter_buf_size = getConfigMap().find("my_buf_size");

    return std::stoi(iter_buf_size->second);
}

int Configuration::initSize()
{
    auto iter_buf_size = getConfigMap().find("my_init_size");

    return std::stoi(iter_buf_size->second);
}

int Configuration::initTime()
{
    auto iter_init_time = getConfigMap().find("my_init_time");

    return std::stoi(iter_init_time->second);
}

int Configuration::updateTime()

{
    auto iter_update_time = getConfigMap().find("my_update_time");

    return std::stoi(iter_update_time->second);
}
#if 1

Configuration* Configuration::m_instance = nullptr;
MutexLock Configuration::_mutex;
Configuration::AutoRelease Configuration::autorelase{};
//双端检查锁 但由于内存读写reorder不安全
Configuration *Configuration::getInstance(const string & confilename)
{
    if(m_instance == nullptr){
        MutexLockGuard lock(_mutex);
        if(m_instance == nullptr)
        {
            m_instance = new Configuration(confilename);
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
Configuration* Configuration::getInstance(const string & confilename)
{
    Configuration * tmp = m_instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);//获取内存fence
    if(tmp == nullptr)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        tmp = m_instance.load(std::memory_order_relaxed);
            if(tmp == nullptr){
                tmp = new Configuration(confilename);
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

    

    //std::ifstream in(_filepath);
    std::ifstream in;
    in.open(_filepath);
    //----------龍
#if 0
    std::stringstream line1;
    std::getline(in,line);
    string line2;
    line1 >> line2;
    cout << "********文件去庐阳的测试" << line2 << endl;
    //----------
#endif
    if(!in.good())
    {
        std::cout << ">> Cann't open file " <<_filepath << std::endl;
        return;
    }
    
    while(getline(in, line))
    {
        std::istringstream record(line);
        record >> key >> val;
        _configMap.insert(make_pair(key, val)); 
        std::cout << "111111111" << std::endl;
    }
}






}
