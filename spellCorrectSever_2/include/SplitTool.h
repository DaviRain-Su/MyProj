#pragma once
#include "cppjieba/Jieba.hpp"

#include <vector>
#include <string>
using std::vector;
using std::string;

namespace  wd
{
const char* const DICT_PATH = "../dict/jieba.dict.utf8";
const char* const HMM_PATH = "../dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../dict/user.dict.utf8";
const char* const IDF_PATH = "../dict/idf.utf8";
const char* const STOP_WORD_PATH = "../dict/stop_words.utf8";
/*
class SplitTool
{
public:
     SplitTool(){}; 
     virtual ~SplitTool()=0;
    //virtual vector<string> cut(const std::string & sentence)=0;
    //virtual void f()=0;
};
*/
class SplitToolCppJieba
{
public:
     SplitToolCppJieba() 
      : _jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH, IDF_PATH,STOP_WORD_PATH){}
     ~SplitToolCppJieba(){}; 
    vector<string> cut(const string & sentence);
private:
    cppjieba::Jieba _jieba;
};
}
