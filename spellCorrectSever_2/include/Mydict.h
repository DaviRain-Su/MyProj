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
#if 1
    void show_dict() const;
    void show_index() const;
    void show_path() const;
#endif
private:
    Mydict(const string & conffilePath = "../conf/my.bat");
    ~Mydict(){}

private:
#if 1
    static Mydict * m_pinstace;
    static MutexLock mutex;
#endif
    string _endictpath;
    string _endindexpath;
    string _cndictpath;
    string _cnindexpath;
#if 0
    static atomic<Mydict*> m_instance;
    static mutex m_mutex;
#endif
    vector<pair<string, int>> _dict;//词典
    map<string, set<int>> _index_table;//索引表
};

}
