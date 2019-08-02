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
string FileProcessor::process(int docid, const string & filename)
{
    string url, title, content;
    cout << ">> filename " << filename << endl;
    readfile(filename, title, url, content);
    string txt = "<doc><docid>" + std::to_string(docid) +
                "</docid><url>" + url + 
                "</url><title>" + title +
                "</title><content>" + content +
                "</content></doc>";
    return txt;
}

void FileProcessor::readfile(const string & filename, string & title, string & url, string & content)
{
    XMLDocument doc;
    doc.LoadFile(filename.c_str());
    if(doc.ErrorID()){
        cout << "doc load error!" << endl;
        return;
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
        title = string(_title);/*赋值给title*/
        url = string(_link);/*赋值被url*/
        
        if(decriptionElement &&  contentElement)
        {

            const char * _description = decriptionElement->GetText();
            const char * _content = contentElement->GetText();


            std::regex re("<[^>]*>");
            std::regex re1("[&#0-9;]");

            string decriptionProcess = std::regex_replace(_description, re, "");
            string contentProcess = std::regex_replace(_content, re1, "");
            string contentProcess1 = std::regex_replace(contentProcess, re1, "");
            /*内容赋值*/
            content = decriptionProcess + contentProcess1;

        }else if(decriptionElement == nullptr && contentElement )
        {
            const char * _content = contentElement->GetText();
            std::regex re("<[^>]*>");
            std::regex re1("[&#0-9;]");

            string contentProcess = std::regex_replace(_content, re1, "");
            string contentProcess1 = std::regex_replace(contentProcess, re1, "");
            content = contentProcess1;

        }else if( decriptionElement && contentElement == nullptr )
        {
            const char * _description = decriptionElement->GetText();


            std::regex re("<[^>]*>");
            std::regex re1("[&#0-9;]");

            string decriptionProcess = std::regex_replace(_description, re, "");
            /*内容赋值*/
            content = decriptionProcess;
        }

        XMLElement * todelete = itemElement;
        itemElement = itemElement->NextSiblingElement("item");
        channelNode->DeleteChild(todelete);
    }

}
}
