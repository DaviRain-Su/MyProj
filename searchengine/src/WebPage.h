#pragma once
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <set>
using std::set;

namespace wd
{
class Configuration;
class WordSegmentation;

class WebPage
{
public:
    WebPage(string & doc, Configuration & conf, WordSegmentation & jieba);
    ~WebPage();

    int getDocId();/*获取文档id*/
    string getDoc();/*获取文档*/
    map<string, int> & getWordMap();/*获取文档的词频统计map*/
    void process(const string  & doc, Configuration & config, WordSegmentation &);/*对格式化文档进行处理*/
    void calcTopK(vector<string> & WordsVec, int k, set<string> & stopWordList);/*求取文档的top词集*/

private:
    const static int TOPK_NUMBER = 20;
    string _doc;/*整片文档包括xml*/
    Configuration & _conf;
    WordSegmentation & _jieba;
    int _docid; /*文档id*/
    string _docTitle;/*文档标题*/
    string _docUrl;/*文档URL*/
    string _docContent;/*文档内容*/
    string _docSummary;/*文档摘要，需要自动生成， 不是固定的*/
    vector<string> _topWord;/*词频最高的前20个*/
    map<string, int> _wordsMap;/*保存每篇文档的所有词语和词频
    包括停词*/
    friend bool operator==(const WebPage & lhs, const WebPage & rhs);/*判断两篇文章是否相等*/
    friend bool operator<(const WebPage & lhs, const WebPage & rhs);/*对文档Docid进行排序*/
};

}
