 ///
 /// @file    TestTinyXml.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-01 09:44:51
 ///
 
#include "tinyxml2.h"  // "" 从当前目录开始搜索
#include <iostream>    // 从系统路径开始搜索
#include <regex>
using std::cout;
using std::endl;
using namespace tinyxml2;

// learning by doing 

void test0()
{
	XMLDocument doc;
	doc.LoadFile("coolshell.xml");
	if(doc.ErrorID()) {
		cout << "doc load error!" << endl;
		return;
	}

#if 0
	XMLElement * itemElement; 
	do {
		itemElement = doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");

		XMLElement * titleElement = itemElement->FirstChildElement("title");
		XMLElement * linkElement = itemElement->FirstChildElement("link");
		XMLElement * contentElement = itemElement->FirstChildElement("content:encoded");

		const char * title = titleElement->GetText();
		const char * link = linkElement->GetText();
		const char * content = contentElement->GetText();

		cout << "title:" << title << endl << endl;
		cout << "link:" << link << endl;
		//cout << "content:" << content << endl;

		std::regex re("<[^>]*>");

		std::string contentProcess = std::regex_replace(content, re, "");
		cout << "content: " << endl
			 << contentProcess << endl;
	} while( (itemElement = itemElement->NextSiblingElement("item")) );
#endif

	//ofstream 输出
	std::string doc1 = 
			"<doc>\n"
			"    <docid>1</docid>\n"
			"    <doctitle></doctitle>\n"
			"</doc>";

	cout << doc1 << endl;

}

void test1()
{
    XMLDocument doc;
    doc.LoadFile("coolshell.xml");
    if(doc.ErrorID()) {
        cout << "doc load error!" << endl;
        return;
    }

    XMLElement * rssNode = doc.FirstChildElement("rss");
    XMLElement * channelNode = rssNode->FirstChildElement("channel");
    XMLElement * itemElement = channelNode->FirstChildElement("item");
    
    while(itemElement){

        XMLElement * titleElement = itemElement->FirstChildElement("title");
        XMLElement * linkElement = itemElement->FirstChildElement("link");
        XMLElement * contentElement = itemElement->FirstChildElement("content:encoded");

        const char * title = titleElement->GetText();
        const char * link = linkElement->GetText();
        const char * content = contentElement->GetText();

        cout << "title:" << title << endl << endl;
        cout << "link:" << link << endl;
        //cout << "content:" << content << endl;

        std::regex re("<[^>]*>");
        std::regex re1("[&#0-9;]");
        std::string contentProcess = std::regex_replace(content, re, "");
        std::string contentProcess1 = std::regex_replace(contentProcess, re1, "");
        
        cout << "content: " << endl
            << contentProcess1 << endl;
        XMLElement * todelete = itemElement;
        itemElement = itemElement->NextSiblingElement("item");
        channelNode->DeleteChild(todelete);     
    }
}
int main(void)
{
    //test0();
    test1();
    return 0;
}
