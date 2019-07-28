#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
using std::set;
using std::unordered_map;
using std::string;
using std::vector;
using std::map;

namespace  wd
{

class SplitTool;

class DictProducer
{
public:
    DictProducer(const string & dir = "./data/EN");
    //构造函数， 专门为中文处理
   // DictProducer(const string & dir, SplitTool * splitTool );
    void build_dict();//创建英文词典
    void build_index();//创建英文索引文件
   // void build_cn_dict();//创建中文词典
   // void build_cn_index(): //创建中文索引文件
    void store_dict(const char * filepath);//将词典写入 文件
    void store_index(const char * filepath);//将索引写入文件
    void show_index() const;//查看索引文件
    void show_files() const;//查看文件路径， 作为测试用
    void show_dict() const;//查看词典，作为测试用
    void push_dict(const string & word);//存储某个单词
    
    
    ~DictProducer() {}
private:
    //void get_files(const char * path);
    void get_files();//获取文件的绝对路径
    void operatorEN(const string & fileepath);//用于引文分词
    string _dir;//语料库文件存放路径
    vector<string> _files;//语料库文件的绝对路径集合
    map<string, int> _dict;// 配置文件内容

    std::unordered_map<string, set<int>> _hashtable;
    SplitTool * _splitTool;// 分词工具
};

}
