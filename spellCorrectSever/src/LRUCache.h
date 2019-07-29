#pragma once
#include "../include/Configuration.h"

#include <iostream>
#include <map>
#include <unordered_map>
using std::unordered_map;
#include <string>
using std::string;
#include <list>
using std::list;

using std::map;

namespace wd
{

struct CachNode{
    string key;
    string  val;

    CachNode(const string & key = "", const  string & val = "")
        : key(key), val(val)
        {}
};

class LRUCache
{
    friend class CacheManger;
public:
    LRUCache(size_t capacity = 10)
    : size(capacity)
    {
        //readFromFile();
    }
    //LRUCache(const LRUCache & cache);

    ~LRUCache() {}
    void readFromFile(const string & filepath = Configuration::getInstance()->cachePath());//从文件中读取缓存信息
    void writeToFile(const string & filepath = Configuration::getInstance()->cachePath());//将缓存信息写入文件
    void update(const LRUCache  & rhs);
    string get(const string & key);
    void addElement(const string & key, const string & val);
private:
    static bool compare(const CachNode & lhs, const CachNode & rhs)
    {
        return lhs.key == rhs.key;
    }
private:
    size_t size;
    list<CachNode> _nodes;
    unordered_map<string, list<CachNode>::iterator> _hash_map;
};

}
