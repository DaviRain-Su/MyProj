#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;
namespace wd
{
class Configuration;

class FileProcessor
{
public:
    FileProcessor(Configuration & conf);
    ~FileProcessor();
    string process(int idx, const string & filename);/*处理一篇文档将其格式化并返回一个长的字符串 _filename 被处理*/
private:
    void readfile( const string & filename, string & title, string & url, string & content);/*获取一篇文章的标题和内容 _fileName 被处理*/
private:
    string _titleFeature;/*文档标题的特征值*/
    Configuration & _conf;    
};

}
