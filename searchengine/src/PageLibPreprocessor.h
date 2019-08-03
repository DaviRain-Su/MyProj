#pragma once
#include "WebPage.h"

#include <vector>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::vector;
using std::pair;
using std::string;

namespace wd
{
class Configuration;
class WordSegmentation;
class WebPage;

class PageLibPreprocessor
{
public:
    PageLibPreprocessor(Configuration & conf , WordSegmentation & jieba);
    ~PageLibPreprocessor();
    void doProcess();/*执行预处理*/

private:
    void readInfromFile();/*根据配置信息读取网页库和位置偏移库的信息*/
    void cutRedundantPage();/*对冗余网页进行去重*/
    void buildInvertIndexTable();/*创建倒排索引表*/
    void storeOnDisk();/*将经过预处理之后的网页库， 位置偏移库和倒排索引表写会到磁盘上*/
private:
    
    Configuration & _conf; /*配置文件对象的引用*/
    WordSegmentation & _jieba;/*分词对象*/
    vector<WebPage> _pageLib;/*网页库容器对象*/
    //vector<string> _vecfiles;/*存放每篇文章没有在被格式化处理的*/
    std::unordered_map<int,pair<int,int>> _offsetLib; /*网页偏移库对象*/
    std::unordered_map< string, vector<pair<int, double>> > _invertIndexTable;/*倒排索引对象*/
};
}

