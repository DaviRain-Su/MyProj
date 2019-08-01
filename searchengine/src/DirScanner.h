#pragma once

#include <vector>
#include <string>
using std::vector;
using std::string;

namespace wd
{

class DirScanner
{
public:
    DirScanner(const string & filepath);
    ~DirScanner();
    
    void operator()();/*重载函数调用运算符，调用traverse*/
    vector<string> & files();/*返货_vecfiles的引用*/
    void show_files();/*测试文件集合打印输出*/
    void traverse(const string & dirname);/*获取某一目录下的所有文件*/
private:
    vector<string> _vecfiles;/*存储每个预料文件的绝对路径*/
    string _filepath;/*某一个目录文件夹路径*/
};

}
