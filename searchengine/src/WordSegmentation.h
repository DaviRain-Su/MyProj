#pragma once
#include "../inc/cppjieba/Jieba.hpp"
#include <vector>
#include <string>
using std::vector;
using std::string;

namespace wd
{
const char * const DICT_PATH = "../inc/dict/jieba.dict.utf8";
const char * const HMM_PATH = "../inc/dict/hmm_model.utf8";
const char * const USER_DICT_PATH = "../inc/dict/user.dict.utf8";
const char * const IDF_PATH = "../inc/dict/idf.utf8";
const char * const STOP_WORD_PATH = "../inc/dict/stop_words.utf8";

class WordSegmentation
{
public:
    WordSegmentation()
        : _jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH){}
    ~WordSegmentation() {}
    vector<string> cut(const string & sentence);
private:
    cppjieba::Jieba _jieba;
};

}
