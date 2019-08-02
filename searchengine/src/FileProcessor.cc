#include "FileProcessor.h"
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
FileProcessor::FileProcessor(const string & filename)
: _fileName(filename)
{
    cout << "FileProcessor()" << endl;
}
/*dctr*/
FileProcessor::~FileProcessor()
{
    cout << "~FileProcessor()" << endl; 
}
/*生成格式化好的网页*/
string FileProcessor::process(int docid)
{
    string url, title, content;
    readfile(title, url, content);
    string txt = "<doc><docid>" + std::to_string(docid) +
                "</docid><url>" + url + 
                "</url><title>" + title +
                "</title><content>" + content +
                "</content></doc>";
    return txt;
}

void FileProcessor::readfile(string & title, string & url, string & content)
{
    XMLDocument doc;
    doc.LoadFile(_fileName.c_str());
    if(doc.ErrorID()){
        cout << "doc load error!" << endl;
        return;
    }

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
        const char * _description = decriptionElement->GetText();
        const char * _content = contentElement->GetText();
        
        title = string(_title);
        url = string(_link);
    
        std::regex re("<[^>]*>");
        std::regex re1("[&#0-9;]");

        string decriptionProcess = std::regex_replace(_description, re, "");
        string contentProcess = std::regex_replace(_content, re1, "");
        string contentProcess1 = std::regex_replace(contentProcess, re1, "");

        content = decriptionProcess + contentProcess1;
        

        XMLElement * todelete = itemElement;
        itemElement = itemElement->NextSiblingElement("item");
        channelNode->DeleteChild(todelete);
    }

}
}
