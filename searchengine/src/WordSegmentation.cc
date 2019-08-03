#include "WordSegmentation.h"

namespace wd
{



vector<string> WordSegmentation::cut(const string & sentence)

{
    vector<string> words;
    string s = sentence;
    _jieba.Cut(s, words, true);
    return words;
}

}
