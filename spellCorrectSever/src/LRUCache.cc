#include "LRUCache.h"
#include "../include/Configuration.h"
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <sstream>
using std::istringstream;
#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
void LRUCache::readFromFile(const string & filepath)
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
        _nodes.push_back(CachNode(key, val));
    }
#if 1
    for(auto it = _nodes.begin(); it != _nodes.end(); ++it)
    {
        cout << "key : " << it->key << "val: " << endl;
    }
    cout << endl;
#endif
    for(auto iter =  _nodes.begin(); iter != _nodes.end(); ++iter)
    {
        _hash_map[iter->key] = iter;
    }
    input.close();

} 
void LRUCache::writeToFile(const string & filepath)
{
    ofstream output(filepath);
    if(!output.good()){
        cout << "fail open file " << filepath << endl;
        return;
    }
    for(auto it = _nodes.begin(); it != _nodes.end(); ++it)
    {
        output << it->key << " " << it->val << "\n";
    }
    output.close();
    
}

//更新cache
void LRUCache::update(const LRUCache  & rhs)
{
    for(auto it = rhs._nodes.begin(); it != rhs._nodes.begin(); ++it)
    {
        _nodes.push_back(*it);
    }
    _nodes.unique(compare);
    for(auto it = _nodes.begin(); it != _nodes.end(); ++it)
    {
        _hash_map[it->key] = it;
    }
}
string LRUCache::get(const string & key)
{
    auto it = _hash_map.find(key);
    if(it == _hash_map.end())
    {
        //找步不到返回一个空子符串
        return string("");
    }else
    {
        string ret = it->second->val;
        _nodes.splice(_nodes.begin(), _nodes, it->second);
        _hash_map[key] = _nodes.begin();
        return ret;
    }
}
void LRUCache::addElement(const string & key, const string & val)
{
    auto it  = _hash_map.find(key);
    if(it == _hash_map.end())
    {
        if(_nodes.size() == size){
            //淘汰元素
            string  deleteKey = _nodes.back().key;
            _nodes.pop_back();
            _hash_map.erase(deleteKey);
        }

        CachNode node(key, val);
        _nodes.push_front(node);
        _hash_map.insert(make_pair(key, _nodes.begin()));
    }else{
        //更新值
        it->second->val = val;
        _nodes.splice(_nodes.begin(), _nodes, it->second);
        _hash_map[key] = _nodes.begin();
    }
}
}//end of namespace wd
