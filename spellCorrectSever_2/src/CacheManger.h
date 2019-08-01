#pragma once
#include "LRUCache.h"
#include "../include/Configuration.h"

#include <vector>
using std::vector;

namespace wd
{

class CacheManger
{
public:
    CacheManger(){
        std::cout <<"CacheManger()" << std::endl;
    }
    ~CacheManger() {
        std::cout << "~CacheManger()" << std::endl;
    }
    
    static void initCache(size_t cache_num = Configuration::getInstance()->threadNum(), const string & filepath = Configuration::getInstance()->cachePath());//从磁盘文件中读取缓存
    static LRUCache & getCache(size_t idx);//获取某个缓存
    static void periodicUpdateCache();//定时更行所有缓存
    static void updateCache();
    /*
     * 假设有N个Cache, 给每个Cache编写一个编号0, 1, 2, ..., N - 1
     * 每隔一段时间(10min)把除了0号cache之外的cache写入到0号cache
     * 之中， 这样0号cache就会共享所有cahce的内容， 再把
     * 0号cache的内容一次写入到1, 2, ..., N - 1号之中， 
     * 经过上述过程之后，所有cache的内容就达到一致状态了。除此之外，
     * 还需将0号cache的内容写入到硬盘cache(文件)， 作为cache的备份
     * 
     * */
private:
    static vector<LRUCache> _cacheList; 
};
}

