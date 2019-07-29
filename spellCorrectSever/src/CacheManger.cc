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
#if 1
/*初始化vector<LRUCache> _cacheList中的元素*/
void CacheManger::initCache(size_t cache_num , const string & filepath)//从磁盘文件中读取缓存
{
#if 1
    std::cout << "cache_num : " << cache_num << std::endl;
    std::cout << "filepath : " << filepath << std::endl;
#endif
    for(size_t idx = 0; idx != cache_num; ++idx)
    {
        _cacheList[idx].readFromFile(filepath);
    }
}
#endif
/*获取某一个缓存cache*/
LRUCache & CacheManger::getCache(size_t idx)
{
    return _cacheList[idx];
}
/*更新全部的缓存cache*/
void CacheManger::updateCache()
{
    std::cout << "updateCache() begin" << std::endl;
#if 1
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
/*定时的更新所有的cache*/
void CacheManger::periodicUpdateCache()
{
#if 0
    std::cout << "periodicUpdateCache()" << std::endl;
#endif
    //updateCache();
#if 1
    std::cout <<"periodicUpdateCache()" << std::endl;
    TimerThread time(Configuration::getInstance()->initTime(), Configuration::getInstance()->updateTime(), std::bind(&CacheManger::updateCache));
    time.start();
#endif
}


}
