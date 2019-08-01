#include "../include/Mydict.h"
#include "../include/Configuration.h"

#include <fstream>
#include <sstream>
#include <cctype>
using std::make_pair;
using std::istringstream;
using std::ifstream;

namespace  wd
{


Mydict::Mydict(const string & conffilePath )
: _endictpath(Configuration::getInstance(conffilePath)->enDcitPpath())
, _endindexpath(Configuration::getInstance(conffilePath)->enIndexPath())
, _cndictpath(Configuration::getInstance(conffilePath)->znDictPath())
, _cnindexpath(Configuration::getInstance(conffilePath)->znIndexPath())
    {
        init();
        show_path();   
#if 0
        show_dict();
        show_index();
#endif
    }

vector<pair<string, int>> & Mydict::getDict()
{
    return _dict;
}
#if 1
void Mydict::show_path()const
{
    std::cout << _endictpath << std::endl;
    std::cout << _endindexpath << std::endl;
    std::cout << _cndictpath << std::endl;
    std::cout << _cnindexpath << std::endl;
}
void Mydict::show_dict() const
{
    for(auto iter = _dict.begin(); iter != _dict.end(); ++iter)
        std::cout << iter->first  << iter->second << std::endl;
    std::cout << std::endl;
}
void Mydict::show_index() const
{
    for(auto iter = _index_table.begin(); iter != _index_table.end(); ++iter)
    {
        std::cout << iter->first << " ";
        for (auto &elem : iter->second)
        {
            std::cout << elem << std::endl;
        }
        std::cout << std::endl;
    }
}
#endif
map<string, set<int>> & Mydict::getIndecTable()
{
    return _index_table;
}

#if 1
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

#if 0
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
    
    //载入英文
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
        record >> key;
        while(record >> val)
        {
             _index_table[key].insert(std::stoi(val));
        }
    }
    in.close();
    //载入中文
    std::ifstream input_(_cndictpath);
    if(!input_.good()){
        std::cout << ">> ifstream open file error " << _cndictpath << std::endl;
        return;
    }
    while(std::getline(input_,line)){
        std::istringstream record(line);
        record >> key >> val;
        _dict.push_back(make_pair(key, std::stoi(val)));
    }
    input.close();
    
    std::ifstream in_(_cnindexpath);
    if(!in_.good()){
        std::cout << ">> iifstream open file error " << _cndictpath << std::endl;
        return ;
    }

    while(std::getline(in_, line)){
        std::istringstream record(line);
        record >> key;
        
        while(record >> val)
        {
             _index_table[key].insert(std::stoi(val));
        }
    }
    in.close();

}





}
