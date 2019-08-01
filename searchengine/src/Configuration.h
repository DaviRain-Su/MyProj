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
    class Autorelease{
        public:
            Autorelease(){}
            ~Autorelease(){
                if(_instance){
                    delete _instance;
                }
            }
    };
public:
   
    static Configuration * getInstance(const std::string & filepath = "../conf/myconf.conf");
    ~Configuration();

    std::set<std::string> & getStopWordList();/*获取停用词集合*/
    std::string ip();
    int port();
    int threadNum();
    
    void showAll(); /*测试接口打印所有信息*/
    void show_stopWord();/*获取停词文件路径*/

private:
    std::map<std::string, std::string> & getConfigMap();/*获取配置文件的map*/
    Configuration(const std::string & filepath);
    void init();
    void  getStopFilePath();
    //void get_files(const std::string & filename);
private:
    std::vector<std::string> _stopfiles; /*停词文件路径*/
    std::string _filepath;/*配置文件路径*/
    std::map<std::string, std::string> _configMap; /*配置文件内容*/
    std::set<std::string> _stopWordList; /*停用词集合*/
    
    static std::mutex _mutex; /*锁*/   
    static Configuration * _instance; 
    static Autorelease _autorelease;
};

}
