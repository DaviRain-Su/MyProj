#include "WebPage.h"
#include "Configuration.h"

#include <iostream>
using std::endl;
using std::cout;


namespace wd
{

WebPage::WebPage(string & doc, Configuration & conf, WordSegmentation & jieba)
    : _doc(doc)
    , _conf(conf)
    , _jieba(jieba)
    {
        cout << " WebPage(string &, Configuration&, WordSegmentation&)" << endl;
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

void WebPage::process(const string & doc, Configuration & config, WordSegmentation & jieba )
{
    
}

void WebPage::calcTopK(vector<string>& WordsVec, int k, set<string> & stopWordList)
{

}

bool operator==(const WebPage & lhs, const WebPage & rhs)
{

}
bool operator<(const WebPage & lhs, const WebPage & rhs)
{

}


}
