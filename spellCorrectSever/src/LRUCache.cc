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
void LRUCache::print()
{
#if 1
    //调试打印两个呢？？？？
    cout << "print()" << endl;
    for(auto it = _nodes.begin(); it != _nodes.end(); ++it)
    {
        cout << ">>key : " << it->key << " >> val: " << it->val << endl;
    }
    cout << endl;
#endif

}

LRUCache LRUCache::operator=(const LRUCache & rhs)
{
   _nodes.erase(_nodes.begin(), _nodes.end());
   _hash_map.erase(_hash_map.begin(), _hash_map.end());
    for(auto it = rhs._nodes.begin(); it != rhs._nodes.end(); ++it)
    {
        _nodes.push_back(*it);
        //_hash_map[*it] = it;
    }
    for(auto iter =  _nodes.begin(); iter != _nodes.end(); ++iter)
    {
        _hash_map[iter->key] = iter;
    }
    return *this;
}
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
        if(line == "") continue;
        istringstream record(line);
        record >> key >> val;
        _nodes.push_back(CachNode(key, val));
    }
#if 1
    //调试打印两个呢？？？？
    cout << "readFromFile()" << endl;
    for(auto it = _nodes.begin(); it != _nodes.end(); ++it)
    {
        cout << ">>key : " << it->key << " >> val: " << it->val << endl;
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
    //ofstream output(filepath, std::ofstream::app);
    ofstream output(filepath);
    if(!output.good()){
        cout << "fail open file " << filepath << endl;
        return;
    }
#if 1
    cout << "writeToFile()" << endl;
    for(auto it = _nodes.begin(); it != _nodes.end(); ++it)
    {
        cout << ">> key : " << it->key << " >> val: "  << it->val << '\n';
    }
    cout << endl;
#endif
    for(auto it = _nodes.begin(); it != _nodes.end(); ++it)
    {
        output  << it->key  << " " << it->val << std::endl;
    }
    output.close();
    
}

//更新cache
void LRUCache::update(const LRUCache  & rhs)
{
#if 1
    std::cout << "update()" << std::endl;
#endif
    for(auto it = rhs._nodes.begin(); it != rhs._nodes.begin(); ++it)
    {
        std::cout << "rhs--key: " << it->key << " rhs--val " << it->val << std::endl; 
    }
     
    for(auto it = rhs._nodes.begin(); it != rhs._nodes.begin(); ++it)
    {
        _nodes.push_back(*it);
    }
    //_nodes.unique(compare);
    for(auto it = _nodes.begin(); it != _nodes.end(); ++it)
    {
        _hash_map[it->key] = it;
    }
    printf("@@@\n");
    print();
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
