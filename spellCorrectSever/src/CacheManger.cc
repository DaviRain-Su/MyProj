#include "CacheManger.h"
#include "TimerThread.h"
#include "../include/Configuration.h"

#include <fstream>
#include <sstream>
using std::ifstream;
using std::ofstream;
using std::istringstream;
#include <iostream>
using std::cout;
using std::endl;
#include <functional>

namespace wd
{

//vector<LRUCache> CacheManger::_cacheList( Configuration::getInstance()->threadNum(), LRUCache()); 
vector<LRUCache> CacheManger::_cacheList( Configuration::getInstance()->threadNum()); 
//vector<LRUCache> CacheManger::_cacheList{ LRUCache()}; 
#if 0
void CacheManger::initCache(size_t idx , const string & filepath)//从磁盘文件中读取缓存
{
        ifstream input(filepath);
        if(!input.good())
        {
            cout << ">> faill open file " << filepath << endl;
            return;
        }
        string key;
        string val;
        string line;
        while(std::getline(input, line))
        {
            istringstream record(line);
            record >> key >> val;
            _cacheList[idx]._nodes.push_back(CachNode(key, val));
        }
#if 1
        for(auto it = _cacheList[idx]._nodes.begin(); it != _cacheList[idx]._nodes.end(); ++it)
        {
            cout << "key : " << it->key << "val: " << endl;
        }
        cout << endl;
#endif
        for(auto iter =  _cacheList[idx]._nodes.begin(); iter != _cacheList[idx]._nodes.end(); ++iter)
        {
            _cacheList[idx]._hash_map[iter->key] = iter;
        }
        input.close();


}
#endif

LRUCache & CacheManger::getCache(size_t idx)//获取某个缓存
{
    return _cacheList[idx];
}

void CacheManger::updateCache()
{
    std::cout << "updateCache() begin" << std::endl;
#if 0
    auto firstCacheNode = _cacheList[0];
    //将1, 2, ..... , N - 1写到第一个0号LRUCache
    for(size_t idx = 1; idx != _cacheList.size(); ++idx)
    {
        firstCacheNode.update(_cacheList[idx]);
    }
    //将0号LRUCache广播给其他LRUCache
    for(size_t idx = 1; idx != _cacheList.size(); ++idx)
    {
        _cacheList[idx].update(firstCacheNode);
    }
    firstCacheNode.writeToFile();
#endif
    std::cout << "updateCache()" << std::endl;
}

void CacheManger::periodicUpdateCache()//定时更行所有缓存
{
    std::cout <<"periodicUpdateCache()" << std::endl;
    TimerThread time(Configuration::getInstance()->initTime(), Configuration::getInstance()->updateTime(), std::bind(&CacheManger::updateCache));
    time.start();
}


}
