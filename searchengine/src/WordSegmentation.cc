#include "PageLibPreprocessor.h"

namespace wd
{

vector<string> PageLibPreprocessor::cut(const string & sentence)
{
    vector<string> words;
    string s = sentence;
    _jieba.Cut(s, words, true);
    return words;
}

}
