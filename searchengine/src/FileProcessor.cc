#include "FileProcessor.h"
#include "Configuration.h"

#include "tinyxml2.h"
#include <iostream>
#include <regex>
using std::regex_replace;
using std::endl;
using std::cout;
using std::string;
using std::vector;

using namespace tinyxml2;

namespace  wd
{
/*ctr*/
FileProcessor::FileProcessor(Configuration & conf)
    :_conf(conf)
{
    cout << "FileProcessor()" << endl;
}
/*dctr*/
FileProcessor::~FileProcessor()
{
    cout << "~FileProcessor()" << endl; 
}
/*生成格式化好的网页*/
vector<string> FileProcessor::process(/*int docid,*/ const string & filename)
{
    string url, title, content;
    cout << ">> filename " << filename << endl;
    /*处理一个文件中文章返回这个文件格式化后的输出字符串*/
    vector<string> result_style;
    result_style = readfile(filename);
#if 1
    cout << "## URL #########" << url << endl;
    cout << "## TITLE #######" << title << endl;
    cout << "## CONTENT #### " << content << endl;
#endif
#if 0
    string txt = "<doc><docid>" + std::to_string(docid) +
        "</docid><url>" + url + 
        "</url><title>" + title +
        "</title><content>" + content +
        "</content></doc>";
#endif
    return result_style;
}

vector<string> FileProcessor::readfile(const string & filename)
{
    static int cnt = 0;/*文章的编号*/
    vector<string> result_string;/*要返回的处理后的一个文件中的所有文件*/
    XMLDocument doc;
    doc.LoadFile(filename.c_str());
    if(doc.ErrorID()){
        cout << "doc load error!" << endl;
    }
    /*这个读取标签的程序也不是全部都能允许运行可以成功
     * 在遇到不标准规范的也会发生读取上出现错误*/
    XMLElement * rssNode = doc.FirstChildElement("rss");
    XMLElement * channelNode  = rssNode->FirstChildElement("channel");
    XMLElement * itemElement = channelNode->FirstChildElement("item");

    while(itemElement){

        XMLElement * titleElement = itemElement->FirstChildElement("title");
        XMLElement * linkElement = itemElement->FirstChildElement("link");
        XMLElement * decriptionElement = itemElement->FirstChildElement("description");
        XMLElement * contentElement = itemElement->FirstChildElement("content:encoded");

        const char * _title = titleElement->GetText();
        const char * _link = linkElement->GetText();
#if 1
        cout << "***** TITLE ****" << _title << endl;
        cout << "***** URL ******" << _link << endl;
#endif
        if(decriptionElement &&  contentElement)
        {

            const char * _description = decriptionElement->GetText();
            const char * _content = contentElement->GetText();


            std::regex re("<200b>|<9a>|&#8212;|&#124;|&#8230;|&#8261;|<[^>]*>|&amp;|&gt;|&lt;|&#8220;|&#8221;|&#8217;|&#8211;|&nbsp;|&quot;|&#8216;|&#8212;");

            string decriptionProcess = std::regex_replace(_description, re, "");
            string contentProcess = std::regex_replace(_content, re, "");
            /*内容赋值*/
            string content = decriptionProcess + contentProcess;
            /*结果赋值出去*/
            string result = "<doc><docid>" + std::to_string(cnt) +
                "</docid><url>" + _link+ 
                "</url><title>" + _title +
                "</title><content>" + content +
                "</content></doc>";
            result_string.push_back(result);

#if 1
            cout << "****CONTENT ******" << content << endl;
#endif
        }else if(decriptionElement == nullptr && contentElement )
        {
            const char * _content = contentElement->GetText();
            std::regex re("<200b>|<9a>|&#8212;|&#124;|&#8230;|&#8261;|<[^>]*>|&amp;|&gt;|&lt;|&#8220;|&#8221;|&#8217;|&#8211;|&nbsp;|&quot;|&#8216;|&#8212;");

            string contentProcess = std::regex_replace(_content, re, "");
            string content = contentProcess;
            string result =  "<doc><docid>" + std::to_string(cnt) +
                "</docid><url>" + _link+ 
                "</url><title>" + _title +
                "</title><content>" + content +
                "</content></doc>";
            result_string.push_back(result);
#if 1
            cout << "****CONTENT ******" << content << endl;
#endif

        }else if( decriptionElement && contentElement == nullptr )
        {
            const char * _description = decriptionElement->GetText();


            std::regex re("<200b>|<9a>|&#8212;|&#124;|&#8230;|&#8261;|<[^>]*>|&amp;|&gt;|&lt;|&#8220;|&#8221;|&#8217;|&#8211;|&nbsp;|&quot;|&#8216;|&#8212;");

            string decriptionProcess = std::regex_replace(_description, re, "");
            /*内容赋值*/
            string content = decriptionProcess;
            string result = "<doc><docid>" + std::to_string(cnt) +
                "</docid><url>" + _link+ 
                "</url><title>" + _title +
                "</title><content>" + content +
                "</content></doc>";
            result_string.push_back(result);
#if 1
            cout << "****CONTENT ******" << content << endl;
#endif
        }

        XMLElement * todelete = itemElement;
        itemElement = itemElement->NextSiblingElement("item");
        channelNode->DeleteChild(todelete);
        cnt++;
    }
    /*返回格式化后的内容*/
    return result_string; 
}
}
