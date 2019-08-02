#include "PageLib.h"
#include "DirScanner.h"
#include "FileProcessor.h"
#include "Configuration.h"

using std::pair;
#include <iostream>
using std::endl;
using std::cout;
#include <fstream>
using std::ofstream;

namespace wd
{
 PageLib::PageLib(Configuration & conf, DirScanner & dirscanner, FileProcessor & fileprocessor)
    : _conf(conf)
    , _dirscanner(dirscanner)
    , _fileprocessor(fileprocessor)
    {
        cout << "PageLib(DirSacnner&,FileProcessor&)" << endl;        
    }
PageLib::~PageLib()
{
    cout << "~PageLib()" << endl;
}
void PageLib::create()
{
    /*处理生成网页库*******************************/
    _dirscanner.operator()();/*目录文件扫描器扫描*/
    vector<string> files;
    files =  _dirscanner.files();
    /*生成扫描的后文件存放到
    文件 内容容器中*/
    size_t  offset  = 0;
    size_t len = 0;
    for(size_t idx = 0; idx != files.size(); ++idx)
    {
        /*将有目录扫描器扫描的到的语料的文件教
         * 由 文件处理器处理后，返回的格式化的
         * 网页库温江内容存放到_vecFiles*/
        
        string text = _fileprocessor.process(idx, files[idx]);
        len =  text.length();
       _vecFiles.push_back(text);
       _offsetLib[idx] = std::make_pair(offset, len);
       offset = len + 1;
    }

}
/*存储网页库和偏移库*/
void PageLib::store()
{
    ofstream outNewIpage(_conf.getNewiPage());/*存储网页库*/
    if(!outNewIpage.good())
    {
        cout << "faill open file" <<  _conf.getNewiPage() << endl;
        return;
    }
    for(auto & page : _vecFiles){
        outNewIpage << page;
    }
    outNewIpage.close();

    ofstream outOffset(_conf.getOffset());/*存储网页偏移库*/
    if(!outOffset.good())
    {
        cout << "faill open file" << _conf.getOffset() << endl;
        return ;
    }
    for(auto & offset : _offsetLib)
    {
        outOffset << offset.first << " "<<  offset.second.first <<  " " << offset.second.second << "\n";
    }
    outOffset.close();
}

}
