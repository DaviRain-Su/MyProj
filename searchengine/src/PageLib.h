#pragma once
#include <map>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::map;


namespace wd
{
class Configuration;
class DirScanner;
class FileProcessor;

class PageLib
{
public:
    PageLib(Configuration & conf, DirScanner & dirscanner, FileProcessor & fileprocessor);
    ~PageLib();

    void create();/*创建网页库*/
    void store();/*存储网页库*/
private:
    Configuration & _conf;/*配置文件对象的引用*/
    DirScanner & _dirscanner;/*目录扫描对象的引用*/
    FileProcessor & _fileprocessor;/*文件处理对象的引用*/
    vector<string> _vecFiles;/*存放格式化后的网页容器*/
    map<int, std::pair<int,int>> _offsetLib;/*存放每篇文章在网页库中的位置信息*/
};

}
