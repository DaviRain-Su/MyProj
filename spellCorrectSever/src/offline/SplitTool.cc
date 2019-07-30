#include "../../include/SplitTool.h"

namespace wd
{

vector<string>  SplitToolCppJieba::cut(const string  & sentence)
{
    vector<string> words;
    string s = sentence;
    //中文分词
    _jieba.Cut(s,words, true);
    return words;
}
}
