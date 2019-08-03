#pragma once
#include <mutex>
#include <string>
#include <map>
#include <set>
#include <vector>

namespace wd
{

class Configuration
{
public:
   
    
    Configuration(const std::string & filepath  = "../conf/myconf.conf");
    ~Configuration();

    std::set<std::string> & getStopWordList();/*获取停用词集合*/
    std::string ip();
    int port();
    int threadNum();
    std::string getRss();
    std::string getNewiPage();
    std::string getPrecessNewiPage();
    std::string getOffset();
    std::string getProcessOffset();
    std::string getInvertIndex();
    void showAll(); /*测试接口打印所有信息*/
    void show_stopWord();/*获取停词文件路径*/


private:
    std::map<std::string, std::string> & getConfigMap();/*获取配置文件的map*/
    void init();
    void  getStopFilePath();
    void get_files(const std::string & filename);
private:
    std::vector<std::string> _stopfiles; /*停词文件路径*/
    std::string _filepath;/*配置文件路径*/
    std::map<std::string, std::string> _configMap; /*配置文件内容*/
    std::set<std::string> _stopWordList; /*停用词集合*/
};

}
