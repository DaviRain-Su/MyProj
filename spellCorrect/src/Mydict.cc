#include "Mydict.h"
#include "../include/Configuration.h"

#include <fstream>
#include <sstream>
#include <cctype>
using std::make_pair;
using std::istringstream;
using std::ifstream;

namespace  wd
{


Mydict::Mydict(const string & conffilePath)
: _endictpath(Configuration::getInstance(conffilePath)->enDcitPpath())
, _endindexpath(Configuration::getInstance(conffilePath)->enIndexPath())
, _cndictpath(Configuration::getInstance(conffilePath)->znDictPath())
, _cnindexpath(Configuration::getInstance(conffilePath)->znIndexPath())
{}

vector<pair<string, int>> & Mydict::getDict()
{
    return _dict;
}

map<string, set<int>> & Mydict::getIndecTable()
{
    return _index_table;
}

#if 0
Mydict* Mydict::m_pinstace = nullptr;
MutexLock Mydict::mutex;

Mydict * Mydict::getInstance()
{
    if(m_pinstace == nullptr){
        MutexLockGuard lock(mutex);
        if(m_pinstace == nullptr){
            m_pinstace = new Mydict();
        }
    }
    return m_pinstace;
}
#endif

#if 1
atomic<Mydict*> Mydict::m_instance;
mutex Mydict::m_mutex;

Mydict *Mydict::getInstance()
{
    Mydict* tmp = m_instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);
    if(tmp == nullptr){
        std::lock_guard<std::mutex> lock(m_mutex);
        tmp = m_instance.load(std::memory_order_relaxed);
        if(tmp == nullptr){
            tmp = new Mydict();
            std::atomic_thread_fence(std::memory_order_release);
            m_instance.store(tmp, std::memory_order_relaxed);
        }
    }
    return tmp;
}


#endif

void Mydict::init(){

    std::ifstream input(_endictpath);
    if(!input.good()){
        std::cout << ">> ifstream open file error " << _endictpath << std::endl;
        return;
    }
    string line;
    string key;
    string val;
    while(std::getline(input,line)){
        std::istringstream record(line);
        record >> key >> val;
        _dict.push_back(make_pair(key, std::stoi(val)));
    }
    input.close();
    
    std::ifstream in(_endindexpath);
    if(!in.good()){
        std::cout << ">> iifstream open file error " << _endictpath << std::endl;
        return ;
    }

    while(std::getline(in, line)){
        std::istringstream record(line);
        record >> key >> val;
        _index_table[key].insert(std::stoi(val));
    }
    in.close();

}





}
