#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;
namespace wd
{

class FileProcessor
{
public:
    FileProcessor(const string & filename);
    ~FileProcessor();
    string process(int idx);/*处理一篇文档将其格式化并返回一个长的字符串 _filename 被处理*/
private:
    void readfile(string & title, string & url, string & content);/*获取一篇文章的标题和内容 _fileName 被处理*/
private:
    string _fileName;/*每一篇文档的绝对路径， 也就是文档的名字*/
    string _titleFeature;/*文档标题的特征值*/
};

}
