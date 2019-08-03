#include "WebPage.h"
#include "Configuration.h"
#include "WordSegmentation.h"

#include <iostream>
using std::endl;
using std::cout;
#include <algorithm>
using std::sort;

namespace wd
{

WebPage::WebPage(const string & doc, Configuration & conf, WordSegmentation & jieba)
    : _doc(doc)
    {
        cout << " WebPage(string &, Configuration&, WordSegmentation&)" << endl;
        /*处理一篇文章*/
        processDoc(doc, conf, jieba);
    }
WebPage::~WebPage()
{
    cout << "~WebPage()" << endl;
}
int WebPage::getDocId()
{
    return _docid;
}
string WebPage::getDoc()
{
    return _doc;
}
map<string, int> & WebPage::getWordMap()
{
    return _wordsMap;
}

void WebPage::processDoc(const string & doc, Configuration & conf, WordSegmentation & jieba)
{
    string docid_start("<docid>");
    string docid_end("</docid>");
    
    /*截取文档的编号**********************************
     * ********************************************/
    std::string::size_type id_begin, id_end;
    id_begin = doc.find(docid_start);
    if(id_begin == std::string::npos)
    {
        std::cout << "no found " << std::endl;
        return;
    }
    id_end = doc.find(docid_end);
    if(id_end == std::string::npos)
    {
        std::cout << "no found " << std::endl;
        return;
    }
    /*要截取的长度*/
    int startPos = id_begin + docid_start.size();
    int cut_len = id_end - startPos;
    string DOCID = doc.substr(startPos, cut_len);
    _docid = std::stoi(DOCID);
    
    /*截取文章标题 ********************************
     * *******************************************/
    string doctitle_start("<title>");
    string doctitle_end("</title>");
    std::string::size_type title_begin, title_end;
    title_begin = doc.find(doctitle_start);
    if(title_begin == std::string::npos)
    {
        std::cout << "no found " << std::endl;
        return;
    }
    title_end = doc.find(doctitle_end);
    if(title_end == std::string::npos)
    {
        std::cout << "no found " << std::endl;
        return;
    }
    /*要截取的长度*/
    startPos = title_begin + doctitle_start.size();
    cut_len = title_end - startPos;
    string TITLE = doc.substr(startPos, cut_len);
    _docTitle = TITLE;
    
    /*获取文档连接url**************************
     * ****************************************/
    string docurl_start("<url>");
    string docurl_end("</url>");
    std::string::size_type url_begin, url_end;
    url_begin = doc.find(docurl_start);
    if(url_begin == std::string::npos)
    {
        std::cout << "no found " << std::endl;
        return;
    }
    url_end = doc.find(docurl_end);
    if(url_end == std::string::npos)
    {
        std::cout << "no found " << std::endl;
        return;
    }
    /*要截取的长度*/
    startPos = url_begin + docurl_start.size();
    cut_len = url_end - startPos;
    string URL = doc.substr(startPos, cut_len);
    _docUrl = URL;
    
    /*获取文档内容*************************************
     * ********************************************/
    string doccontent_start("<content>");
    string doccontent_end("</content>");
    std::string::size_type content_begin, content_end;
    content_begin = doc.find(doccontent_start);
    if(content_begin == std::string::npos)
    {
        std::cout << "no found " << std::endl;
        return;
    }
    content_end = doc.find(doccontent_end);
    if(content_end == std::string::npos)
    {
        std::cout << "no found " << std::endl;
        return;
    }
    /*要截取的长度*/
    startPos = content_begin + doccontent_start.size();
    cut_len = content_end - startPos;
    string CONTENT = doc.substr(startPos, cut_len);
    _docContent = CONTENT;
    /*获取文档摘要 *** 这里偷懒， 摘要就是内容了*/
    _docSummary = _docContent;

    /*获取停词并对文章进行处理，并且提取前20个频率最高的词汇*/  
    set<string> stopWordList = conf.getStopWordList();
    /*对一篇文章的内容进行切分， 返回的是分词之后的 vector<string>*/
    vector<string> words = jieba.cut(_docContent);
    /*将一篇文章中的前20个出现频率最高的词汇存储到 _topWord
     * TOPK_NUMBER 是设定的要存取的频率最高的多少的单词*/
    calcTopK(words, TOPK_NUMBER , stopWordList);
}

void WebPage::calcTopK(vector<string>& WordsVec, int k, set<string> & stopWordList)
{
    for(auto & word : WordsVec)
    {
        /*排除文章中的停词*/
        if(stopWordList.find(word) != stopWordList.end())
        { continue; }
        else
        {
            /*将不是停词的单词放入到 _wordsMap中去*/
            _wordsMap[word]++;
        }
    }
    /*存放的的pair 是每个单词一节单词对应的词频
     * pair <sring, int> */
    vector<std::pair<string, int>> wordvec;
    for(auto it : _wordsMap) /*_wordsMap 的每一个元素的类型是pair<string, int> */
    {
        /*将_wordMap中的每元素类型, 存放到wordvec, vecs会根据每个单词出现的词频进行排序*/
        wordvec.push_back(it);
    }
    /*sort vector<pair<string, int>> wordvec*/
    /*根据每个单词出现的词频进行排序， 词频高的排在最前面*/
    sort(wordvec.begin(), wordvec.end(), Compare());
    /*获取前k 个出现的单词*/
    for(int i = 0; i < k; i++)
    {
        /*存储前k个单词到 vector<string> _topWord*/
        _topWord.push_back(wordvec[i].first);
    }
}
/*判断篇文章是否相同的函数*/
bool operator==(const WebPage & lhs, const WebPage & rhs)
{
    int critial_value = 11;
    set<string> none_repate_word(lhs._topWord.begin(),lhs._topWord.end());
    for(auto & word : rhs._topWord)
    {
        none_repate_word.insert(word);
    }
    int count_repate = 2 * lhs._topWord.size() - none_repate_word.size();
    if(count_repate > critial_value) return true; /*若两篇文章中的top20个单词中有超过11的单词相同的则
    认为两篇文章是相同*/
    else return false;
}
bool operator<(const WebPage & lhs, const WebPage & rhs)
{
    return lhs._docid < rhs._docid;  
}


}
