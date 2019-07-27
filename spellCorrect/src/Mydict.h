#pragma once
#include "../include/MutextLock.h"



#include <vector>
#include <set>
#include <string>
#include <utility>
#include <map>
#include <atomic>
#include <mutex>
using std::mutex;
using std::atomic;
using std::vector;
using std::pair;
using std::string;
using std::set;
using std::map;
namespace  wd
{

class Mydict
{
public:
    static Mydict* getInstance();
    //void init(const string & dicEnPath/*, const string & dicCnPath*/);
    void init();
    vector<pair<string, int>> & getDict();//获取词典
    map<string, set<int>> & getIndecTable();//获取索引表

private:
    Mydict(const string & conffilePath = "../conf/my.bat");
    ~Mydict(){}

private:
#if 0
    static Mydict * m_pinstace;
    static MutexLock mutex;
#endif
    string _endictpath;
    string _endindexpath;
    string _cndictpath;
    string _cnindexpath;
    static atomic<Mydict*> m_instance;
    static mutex m_mutex;

    vector<pair<string, int>> _dict;//词典
    map<string, set<int>> _index_table;//索引表
};

}
