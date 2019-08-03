
#include "PageLibPreprocessor.h"
#include "Configuration.h"
#include "WordSegmentation.h"
//#include "WebPage.h"
#include "WebPage.h"

#include <cmath>//log()
#include <iostream>
using std::endl;
using std::cout;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <sstream>
using std::istringstream;

namespace wd
{

#if 1

PageLibPreprocessor::PageLibPreprocessor(Configuration & conf,WordSegmentation & jieba)
    : _conf(conf)
    , _jieba(jieba)
    {
        cout << "PageLibPreprocessor(Configuration&, WebSegmentation&)" << endl;
    }
#endif

PageLibPreprocessor::~PageLibPreprocessor()
{
    cout << "~PageLibPreprocessor()" << endl;
}

/*一次执行所有的操作*/
void PageLibPreprocessor::doProcess()/*执行预处理*/
{
   readInfromFile();
   cutRedundantPage();
   buildInvertIndexTable();
   storeOnDisk();
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
    for(string & doc : vecfiles)
    {
        cout << "********************************************************* " << doc << endl;
        WebPage webpage(doc, _conf, _jieba);
        _pageLib.push_back(webpage);
    }


}
void PageLibPreprocessor::cutRedundantPage()/*对冗余网页进行去重*/
{
    /*重新将去重后的网页存储到_pageLib中*/
    set<WebPage> pagelib(_pageLib.begin(), _pageLib.end());
    _pageLib.erase(_pageLib.begin(), _pageLib.end());
    _pageLib.insert(_pageLib.begin(), pagelib.begin(), pagelib.end());
    /*重新赋值改变网易偏移库的*/
    _offsetLib.erase(_offsetLib.begin(), _offsetLib.end());
    size_t offset = 0;
    for(auto & web : _pageLib)
    {
        int len = web.getDoc().size();
        _offsetLib[web.getDocId()] = std::make_pair(offset, len);
        offset += len;
    }

}
void PageLibPreprocessor::buildInvertIndexTable()/*创建倒排索引表*/
{
    /*构造一个大map*/
    map<string, int> bigMap;
    for(auto &web : _pageLib )
    {
        auto smallMap = web.getWordMap();
        for(auto it = smallMap.begin(); it != smallMap.end(); ++it)
        {
            bigMap[it->first] += it->second;
        }/*将大map初始化*/
    }

    /*************/
    for(auto & wed : _pageLib)/*针对的计算所有的网页*/
    {
        /*下面试针对每一片文章都是这样操作*/
        int page_cnt = _pageLib.size();/*文章的总数*/
        auto smallMap = wed.getWordMap();/*获得某一个网页的map*/
        vector<double> weight(smallMap.size(), 0.0);/*用于存储一篇文章中的
        计算得到的每个单词的权重， 用于后面的归一化*/
        for(auto it = smallMap.begin(); it != smallMap.end(); ++it)
        {
            /*计算一个网页中的小map的所有的单词， 起始是从第一篇文章开始的*
             * */
            /*依次每个单词的出现的频率*/
            int elem_TF = it->second;/*得到这个单词在这一篇文章中词频*/
            int total_DF = bigMap[it->first];/*得到这个单词在所有文章中的词频*/
            double IDF;
            IDF = log(page_cnt / (total_DF + 1))/log(2);/*计算的以2为底的对数*/
            double w = elem_TF * IDF;
            weight.push_back(w);/*将一片文章中各个单词计算得到的权重存储到weight*/
        }
        /*计算需要归一化的底*/
        double totalWegit2 = 0;
        for(auto elem : weight)
        {
            totalWegit2 += elem * elem;
        }
        /*对一篇文章中的单词的权重进行归一化处理*/
        vector<double> norm_weight(smallMap.size(), 0.0);
        for(auto elem : weight)/*针对每一权重进行归一化后存到归一化后的向量中*/
        {
            double tmp = elem / sqrt(totalWegit2);
            norm_weight.push_back(tmp);/*将归一化后的权重存储到向量中*/
        }

        /*****************************************************/
        /*这是将处理后的权重信息加入大道倒排文件中*/
        size_t idx = 0;
        for(auto it = smallMap.begin(); it !=  smallMap.end(); ++it)
        {
            /*插入到倒排列表中，将一篇文章的所有单词插入到倒排列表中*/
            _invertIndexTable[it->first].push_back(std::make_pair(wed.getDocId(), norm_weight[idx]));
            ++idx;
        }
    }
}
void PageLibPreprocessor::storeOnDisk()/*将讲过预处理之后的网页库和网页偏库和倒排索引表写回到磁盘
*/
{
    /*将网页库存储到文件中*/
    ofstream out_newipage(_conf.getPrecessNewiPage());
    if(!out_newipage.good()){
        cout << "fail open the file " << _conf.getProcessOffset() << endl;
        return;
    }
    for(auto &wed : _pageLib)
    {
        out_newipage << wed.getDoc();
    }
    out_newipage.close();
    /*将网页偏移库存储到文件中*/
    std::ofstream out_offset(_conf.getProcessOffset());
    if(!out_offset)
    {
        cout << "fail open the file" << _conf.getPrecessNewiPage() << endl;
        return;
    }
    for(auto & elem : _offsetLib)
    {
        out_offset << elem.first << " " << elem.second.first << " " << elem.second.second << "\n";
    }
    out_offset.close();
    /*将倒排索引表存储到文件中*/
    ofstream out_invertIndex(_conf.getInvertIndex());
    if(!out_invertIndex.good())
    {
        cout << "fail to open the file " << _conf.getInvertIndex() << endl;
        return;
    }
    for(auto & elem : _invertIndexTable)
    {
        out_invertIndex << elem.first << " ";
        for(auto &tmp : elem.second)
        {
            out_invertIndex << tmp.first << " " << tmp.second << " ";
        }
        out_invertIndex << "\n";
    }
    out_invertIndex.close();

}




}
