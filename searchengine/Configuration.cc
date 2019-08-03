#include "Configuration.h"
#include "DirScanner.h"/*获取停词集合使用*/

#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#include <iostream>
#include <fstream>
using std::ifstream;

using std::cout;
using std::endl;

using std::string;
using std::map;
using std::make_pair;
using std::set;
using std::mutex;

#define ERROR_CHECK(ret, retVal, funcName)\
{\
    if(ret == retVal){\
        printf("errno = %d\n", errno);\
        perror(funcName);\
    }\
}
namespace wd
{
/*static 变量这里是定义*/
Configuration::Autorelease Configuration::_autorelease{};
Configuration * Configuration::_instance = nullptr;
mutex Configuration::_mutex;
/*双检查锁机制*/
Configuration * Configuration::getInstance(const string & filepath)
{
    if(_instance == nullptr)
    {
        std::lock_guard<mutex> lock(_mutex); 
        if(_instance == nullptr){
            _instance = new Configuration(filepath);
        }
    }
    return _instance;
}
/*ctr*/
Configuration::Configuration(const string & filepath)
    :_filepath(filepath)
{ 
    init();/*初始化ConfMap*/
    cout << "Configuration(const string & filepath)"  << endl; 
}
/*dctr*/
Configuration::~Configuration()
{ 
    cout << "~Configuration()" << endl;  
}
/*初始化文件内容map*/
void Configuration::init()
{
    ifstream input(_filepath);
    if(!input.good())
    {
        cout << ">> fail open file" << _filepath << endl;
        return;
    }
    string key;//配置文件的key值
    string val;//配置文件的val值
    while(input >> key >> val)
    {
        _configMap.insert(make_pair(key, val));
    }
    input.close();
}
/*获取文件的内容map*/
map<string, string> & Configuration::getConfigMap()
{
    return _configMap;
}
/*获取服务器的ip*/
string Configuration::ip()
{
   map<string, string>& ConfMap = getConfigMap(); 

   return ConfMap["my_ip"];
}
/*获取服务器的端口号*/
int Configuration::port()
{
    map<string,string> & ConfMap = getConfigMap();
    return stoi(ConfMap["my_port"]);
}
/*获取线程的数量*/
int Configuration::threadNum()
{
    map<string,string> & ConfMap = getConfigMap();
    return stoi(ConfMap["my_thread_num"]);
    
}
string Configuration::getRss()
{
    auto & ConfMap = getConfigMap();
    return ConfMap["my_rss_path"];
}
/*获取停词的文件路径*/
void  Configuration::getStopFilePath()
{
    map<string,string> & ConfMap = getConfigMap();
    string stopwordpath =  ConfMap["my_stop_list"];
    DirScanner scanner(stopwordpath);
    scanner.operator()();/*构建文件集合*/

    _stopfiles = scanner.files();/*返回文件集合*/
    //get_files(stopwordpath);     
}
/*初始化set<string> _stopWordList*/
set<string> & Configuration::getStopWordList()
{
    /*构造_stopWordList容器中的内容*/
    getStopFilePath();
    /*遍历存放发_stopfiles容器中的文件路径
     * 逐个地处理每个文件
     * 将每个文件的中的停词存放到
     * set<stirng> _stopWordList*/
    for(auto it = _stopfiles.begin(); it != _stopfiles.end(); ++it)
    {

        std::ifstream input(*it);
        if(!input.good())
        {
            cout << ">> fail open file " << *it << endl;
        }
        string key;/*停词集合的key*/
        while(std::getline(input,key))
        {
            cout<<key<<endl;
            _stopWordList.insert(key);
        }
        input.close();
    }
    return _stopWordList;


}

void Configuration::showAll()
{
#if 1
    cout << ">> ip : " << ip() << endl;
    cout << ">> port : " << port() << endl;
    cout << ">> threadNum : " << threadNum() << endl;
    cout << ">> rss path : " << getRss() << endl;
#endif
    getStopFilePath();
    for(auto iter = _stopfiles.begin(); iter != _stopfiles.end(); ++iter)
    {
        cout << " >> file : " << *iter << endl;
    }
    for(auto it = _configMap.begin(); it != _configMap.end(); ++it)
    {
        cout << ">> key : " << it->first << " >> val : " << it->second << endl;
    }
}
void Configuration::show_stopWord()
{
    getStopWordList();
#if 0
    for(auto it = _stopWordList.begin(); it != _stopWordList.end(); ++it)
    {
        cout << " >> word :  " << *it << endl;
    }
#endif
}
#if 0
/*获取一个目录下的所有的文件路径存放到_stopfiles
 * 使用linux的系统调用接口实现，查找一个目录写的所有文件
 * 并拼装成一个个的文件路径*/
void Configuration::get_files(const string & filename)
{
    DIR * dir;
    dir = opendir(filename.c_str());
    ERROR_CHECK(dir, NULL, "opendir");
    struct dirent *p;
    char tmpPath[1024] = {0};
    while( (p = readdir(dir)) != NULL )
    {
        if(!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
        { continue; }
        if(DT_DIR == p->d_type)
        {
            sprintf(tmpPath, "%s%s%s", filename.c_str(), "/",p->d_name);
        }else if(DT_REG == p->d_type)
        {
            sprintf(tmpPath, "%s%s%s", filename.c_str(), "/",p->d_name);
            _stopfiles.push_back(tmpPath);
        }
    }
    closedir(dir);
}
#endif

}
