#include "../../include/DictProducer.h"
#include "../../include/SplitTool.h"

#include <string.h>
#include <sys/types.h>
#include <dirent.h>

//#include <sys/stat.h>
//#include <fcntl.h>

#define ERROR_CHECK(ret, retVal, funcName){\
    if(ret == retVal){\
        printf("errno=%d\n", errno);\
        perror(funcName);\
    }\
}
#include <locale>
#include <codecvt>

#include <regex>
using std::regex_replace;
#include <iostream>
#include <fstream>
#include <cctype>
#include <utility>
using std::pair;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::cout;
using std::wstring;

namespace wd
{

DictProducer::DictProducer(const string & dir)
    : _dir(dir)
      , _splitTool(nullptr)
    {
        cout << "_dir >> " << _dir << endl;   
    }
DictProducer::DictProducer(const string & dir, SplitToolCppJieba* splitTool )
    : _dir(dir)
      , _splitTool(splitTool)
    {
        cout << "DictProducer(const string, SplitTool*)" << endl;
    }

void DictProducer::build_cn_dict()
{
    get_files();

    //处理vector<string> _files文件路径的集合
    
    for(auto & iter : _files)
    {
        cout << ">> files: " << iter << endl;
        //operatorCN(iter);
    }
}
std::wstring DictProducer::StringToWstring(const std::string str)
{
    unsigned len = str.size() * 2;//预留字节数
    setlocale(LC_CTYPE, "");//必须调用此函数
    wchar_t *p = new wchar_t[len];//申请一段内存存放装换后的字符串
    mbstowcs(p,str.c_str(), len);//装换
    std::wstring str1(p);
    delete[] p;//释放申请的内存
    return str1;
}
std::string DictProducer::WstringToString(const std::wstring str)
{
    //wstring to stirng
    unsigned len = str.size() * 4;
    setlocale(LC_CTYPE, "");
    char * p = new char[len];
    wcstombs(p, str.c_str(),len);
    std::string str1(p);
    delete []p;
    return str1;
}
/*处理中文分词*/
void DictProducer::operatorCN(const string & filepath)
{

    ifstream input(filepath);
    if(!input.good()){
        cout << "open file is failed!" << filepath <<  endl;
    }
    //将文章的标点符号删除
    //中文标点符号集合
    std::string line_read;
    std::vector<std::string> files;
    while(std::getline(input, line_read))
    {
#if 1
        //std::locale::global(std::locale("chs"));
        wstring Wstring = StringToWstring(line_read);
        Wstring = std::regex_replace(Wstring,std::wregex(L"[^\u4E00-\u9FA5]"), std::wstring(L" "));
        string converted_str = WstringToString(Wstring);
#endif
        files.push_back(converted_str);
    }
    input.close();
    //中文分词
    //
    //
    vector<string> words;
    for(auto iter = files.begin(); iter != files.end(); ++iter)
    {
         words = _splitTool->cut(*iter); 
         for(auto & word : words)
         { 
            if(word == " ") continue;
            else push_dict(word);  
         } 
    }
}
size_t DictProducer::nBytesCode(const char ch)
{
    if(ch & (1 << 7))
    {
        int nBytes = 1;
        for(int idx = 0; idx != 6; ++idx)
        {
            if(ch & (1 << (6 - idx)))
            {
                ++nBytes;
            }else
                break;
        }
        return nBytes;
    }
    return 1;
}
size_t DictProducer::length(const string & str)
{
    size_t ilen = 0;
    for(size_t idx = 0; idx != str.size(); ++idx)
    {
        int nBytes = nBytesCode(str[idx]);
        idx += (nBytes - 1);
        ++ilen;
    }
    return ilen;
}
void DictProducer::build_cn_index()
{
    vector<pair<string, int>> dics;
    for(auto iter = _dict.begin(); iter != _dict.end();++iter)
    {
        dics.push_back(make_pair(iter->first, iter->second));
    }

    size_t idx = 0;
    for(auto iter = dics.begin(); iter != dics.end(); ++iter)
    {
        string  word = iter->first;
        /*这里是中文的拆分为单个字符*/
        wstring temp_word = StringToWstring(word);
        for(auto it = temp_word.begin(); it != temp_word.end(); ++it)
        {
            wstring wstr;
            wstr.push_back(*it);
            std::cout << "------ " << WstringToString(wstr)<< std::endl;
           _hashtable[WstringToString(wstr)].insert(idx); 
        }
        idx++;
    }

}
void DictProducer::build_dict()
{
    get_files();

    //process vector<string> _files;
    for(auto & iter : _files)
    {
        cout << ">> file: " << iter << endl;
        operatorEN(iter); 
    }
}

void DictProducer::build_index()
{
    vector<pair<string, int>> dics;
    for(auto iter = _dict.begin(); iter != _dict.end();++iter)
    {
        dics.push_back(make_pair(iter->first, iter->second));
    }

    size_t idx = 0;
    for(auto iter = dics.begin(); iter != dics.end(); ++iter)
    {
        auto word = iter->first;
        /*这里是英文的拆分为单个字符*/
        for(auto & ch : word)
        {
            //string 构造函数的使用sting(size_t count, charT );
            //将一个char 构造为string
            _hashtable[string(1,ch)].insert(idx);
        }
        idx++;
    }

}
void DictProducer::push_dict(const string & word)
{
    auto findIter = _dict.find(word);
    if(findIter == _dict.end())
        _dict[word]++;
    else{
        findIter->second++;
    }
}
void DictProducer::store_dict(const char * filepath)
{
    //涉及到了文件IO的使用输出到文件中
    ofstream output(filepath);
    if(!output.good()){
        cout << ">> ofstream open file error " << filepath << endl;
        return;
    }

    for(auto iter = _dict.begin(); iter != _dict.end(); ++iter)
    {
        output <<  iter->first << " " <<  iter->second << "\n";
    }
    output.close();
}
void DictProducer::store_index(const char * filepath)
{
    ofstream output(filepath);
    if(!output.good())
    {
        cout << ">> ofstream open file error " << filepath << endl;
        return;
    }
    for(auto iter = _hashtable.begin(); iter != _hashtable.end(); ++iter)
    {
        output  << iter->first << " ";
        for(auto it = (iter->second).begin(); it != (iter->second).end(); ++it )
        {
            output << (*it) << " ";
        }
        output << "\n";
    }
    output.close();

}
void DictProducer::show_files() const
{
#if 1
    for(auto iter : _files)
        cout << ">> file: " << iter << endl;
#endif

}
void DictProducer::show_dict() const
{
#if 1
    for(auto iter = _dict.begin(); iter != _dict.end(); ++iter)
    {
        cout <<  iter->first << " ---- " <<  iter->second << endl;
    }
#endif
}
void DictProducer::show_index() const
{
    for(auto iter = _hashtable.begin(); iter != _hashtable.end(); ++iter)
    {
        cout << iter->first << ": ";
        for(auto it = (iter->second).begin(); it != (iter->second).end(); ++it )
        {
            cout << *it << " ";
        }
        cout << endl;
    }
}
/*获取文件路径存储文件的路径集合到vector<stirng> _files
 *这里可以中英文混用*/
void DictProducer::get_files()
{
    DIR * dir;
    dir = opendir(_dir.c_str());
    ERROR_CHECK(dir, NULL, "opendir");
    struct dirent *p;
    char tmpPath[1024] = {0};
    while((p = readdir(dir)) != NULL)
    {
        if(!strcmp(p->d_name,".") || !strcmp(p->d_name,".."))
        {
            continue;
        }
        if(DT_DIR == p->d_type)
        {
            sprintf(tmpPath, "%s%s%s",_dir.c_str() , "/",p->d_name);
            //get_files();
        } else if(DT_REG == p->d_type)
        {
            sprintf(tmpPath, "%s%s%s", _dir.c_str(), "/", p->d_name);
            _files.push_back(tmpPath);
        }
    }
    closedir(dir);
}



/*这里是特定的对于英文来说的分词*/
void DictProducer::operatorEN(const string & filename)
{

    //打开文件
    ifstream input(filename);
    if(!input.good()){
        cout << "open file is failed!" << filename <<  endl;
    }
    //将文章的标点符号删除
    std::string line;
    std::vector<std::string> file;
    while(std::getline(input, line))
    {
        for (auto & ch : line)
        {
            if(isdigit(ch) || ispunct(ch))
                ch = ' ';
            ch = tolower(ch);
        }
        file.push_back(line);
    }
    input.close();

    std::vector<std::string> words;
    //分词
    char temp[20] = {0};
    for(auto lineno = file.begin(); lineno != file.end(); ++lineno)
    {
        auto i = lineno->begin();
        int k = 0;
        for(;i != lineno->end(); ++i)
        {
            //从75到92的分词核心，在于申请了一个用于存放单词的位置
            std::string tempWord;
            if(*i == ' ' || *i == '\n' || *i == '\t')
            {
                if(i == line.begin()){
                    continue;
                }else{
                    temp[k] = 0;
                    tempWord = std::string(temp);
                    if(tempWord.size() != 0){
                        words.push_back(tempWord);
                    }
                    k = 0;
                }
            }else{
                temp[k] = *i;
                k++;
            }
        }
    }
    //放入map<string, int>
    for(auto & word : words)
    {
        push_dict(word);
    }
}

}
