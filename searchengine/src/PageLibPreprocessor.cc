#include "PageLibPreprocessor.h"
#include "Configuration.h"
#include "WordSegmentation.h"
//#include "WebPage.h"
#include "WebPage.h"

#include <iostream>
using std::endl;
using std::cout;
#include <fstream>
using std::ifstream;
#include <sstream>
using std::istringstream;

namespace wd
{

PageLibPreprocessor::PageLibPreprocessor(Configuration & conf, WebSegmentation & jieba)
    : _conf(conf)
    , _jieba(jieba)
    {
        cout << "PageLibPreprocessor(Configuration&, WebSegmentation&)" << endl;
    }
PageLibPreprocessor::~PageLibPreprocessor()
{
    cout << "~PageLibPreprocessor()" << endl;
}

void PageLibPreprocessor::doProcess()/*执行预处理*/
{

}
void PageLibPreprocessor::readInfromFile()/*根据配置信息读取网页库和位置偏移库*/
{
    /*读取网页偏移信息*/
    ifstream in_offset(_conf.getOffset());/*读取网页偏移库*/
    if(!in_offset.good())
    {
        cout << "fail open file " << _conf.getNewiPage() << endl;
        return;
    }
    string line;
    /*设计文档的id, 在网页库的偏移位置信息offset， 还有一篇文档的长度*/
    int docid, offset, len;
    while(std::getline(in_offset,line))
    {
        std::istringstream record(line);
        record >> docid >> offset >> len;/*文档的读取*/
        _offsetLib[docid] = std::make_pair(offset, len);
    }
    in_offset.close();

    vector<string> vecfiles;
    /*读取每一篇网页的信息*/
    std::ifstream in_newipage(_conf.getNewiPage());
    if(!in_newipage.good())
    {
        cout << "fail to open file " << _conf.getNewiPage() << endl;
        return;
    }
    for(auto it : _offsetLib)
    {
        int offset = it.second.first;/*读取存储的偏移信息，即每一篇文章在newipage中位置*/
        int len = it.second.second;/*读取存储的长度大小， 即每一篇文章在newipage中长度大小*/
        in_newipage.seekg(offset, in_newipage.beg);/*定位每一篇文章在输入流中读取的位置信息*/
        string buf(len, '\0');/*申请出读取出要存放法内存*/
        in_newipage.read(&buf[0], len);/*将从输入流中读取固定大小长度的内容存方到buf*/
        vecfiles.push_back(buf);/*将读取出来的内存存放到_vecfiles,即用于存放每篇文章的容器， 这个容器中存放
        的文章内容是，读取出来的网页库的原生资料没有被预处理的*/
    }
    in_newipage.close();

    /*处理每一篇读取出来的文章*/
    for(string  doc : vecfiles)
    {
         WebPage webpage(doc, _conf, _jieba);
        _pageLib.push_back(webpage);
    }
    

}
void PageLibPreprocessor::cutRedundantPage()/*对冗余网页进行去重*/
{
    set<WebPage> pagelib(_pageLib.begin(), _pageLib.end());
}
void PageLibPreprocessor::buildInvertIndexTable()/*创建倒排索引表*/
{

}
void PageLibPreprocessor::storeOnDisk()/*将讲过预处理之后的网页库和网页偏库和倒排索引表写回到磁盘
*/
{

}




}
